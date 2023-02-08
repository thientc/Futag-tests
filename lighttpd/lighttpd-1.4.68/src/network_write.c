#include "first.h"

#include "network_write.h"

#include "base.h"
#include "ck.h"
#include "log.h"

#include <sys/types.h>
#include "sys-socket.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>


/* on linux 2.4.x you get either sendfile or LFS */
#if defined HAVE_SYS_SENDFILE_H && defined HAVE_SENDFILE \
 && (!defined _LARGEFILE_SOURCE || defined HAVE_SENDFILE64) \
 && defined(__linux__) && !defined HAVE_SENDFILE_BROKEN
# ifdef NETWORK_WRITE_USE_SENDFILE
#  error "can't have more than one sendfile implementation"
# endif
# define NETWORK_WRITE_USE_SENDFILE "linux-sendfile"
# define NETWORK_WRITE_USE_LINUX_SENDFILE
#endif

#if defined HAVE_SENDFILE && (defined(__FreeBSD__) || defined(__DragonFly__))
# ifdef NETWORK_WRITE_USE_SENDFILE
#  error "can't have more than one sendfile implementation"
# endif
# define NETWORK_WRITE_USE_SENDFILE "freebsd-sendfile"
# define NETWORK_WRITE_USE_FREEBSD_SENDFILE
#endif

#if defined HAVE_SENDFILE && defined(__APPLE__)
# ifdef NETWORK_WRITE_USE_SENDFILE
#  error "can't have more than one sendfile implementation"
# endif
# define NETWORK_WRITE_USE_SENDFILE "darwin-sendfile"
# define NETWORK_WRITE_USE_DARWIN_SENDFILE
#endif

#if defined HAVE_SYS_SENDFILE_H && defined HAVE_SENDFILEV && defined(__sun)
# ifdef NETWORK_WRITE_USE_SENDFILE
#  error "can't have more than one sendfile implementation"
# endif
# define NETWORK_WRITE_USE_SENDFILE "solaris-sendfilev"
# define NETWORK_WRITE_USE_SOLARIS_SENDFILEV
#endif

/* not supported so far
#if defined HAVE_SEND_FILE && defined(__aix)
# ifdef NETWORK_WRITE_USE_SENDFILE
#  error "can't have more than one sendfile implementation"
# endif
# define NETWORK_WRITE_USE_SENDFILE "aix-sendfile"
# define NETWORK_WRITE_USE_AIX_SENDFILE
#endif
*/

#if defined HAVE_SYS_UIO_H && defined HAVE_WRITEV
# define NETWORK_WRITE_USE_WRITEV
#endif

#if defined(HAVE_MMAP) || defined(_WIN32) /*(see local sys-mmap.h)*/
#ifdef ENABLE_MMAP
# define NETWORK_WRITE_USE_MMAP
#endif
#endif


__attribute_cold__
static int network_write_error(int fd, log_error_st *errh) {
  #if defined(__WIN32)
    int lastError = WSAGetLastError();
    switch (lastError) {
      case WSAEINTR:
      case WSAEWOULDBLOCK:
        return -3;
      case WSAECONNRESET:
      case WSAETIMEDOUT:
      case WSAECONNABORTED:
        return -2;
      default:
        log_error(errh,__FILE__,__LINE__,"send failed: %d %d",lastError,fd);
        return -1;
    }
  #else /* __WIN32 */
    switch (errno) {
      case EAGAIN:
      case EINTR:
        return -3;
      case EPIPE:
      case ECONNRESET:
        return -2;
      default:
        log_perror(errh,__FILE__,__LINE__,"write failed: %d",fd);
        return -1;
    }
  #endif /* __WIN32 */
}

__attribute_cold__
static int network_remove_finished_chunks(chunkqueue * const cq, const off_t len) {
    force_assert(len >= 0);
    chunkqueue_remove_finished_chunks(cq);
    return 0;
}

inline
static ssize_t network_write_data_len(int fd, const char *data, off_t len) {
  #if defined(__WIN32)
    return send(fd, data, len, 0);
  #else /* __WIN32 */
    return write(fd, data, len);
  #endif /* __WIN32 */
}

static int network_write_accounting(const int fd, chunkqueue * const cq, off_t * const p_max_bytes, log_error_st * const errh, const ssize_t wr, const off_t toSend) {
    if (wr >= 0) {
        *p_max_bytes -= wr;/*(toSend > 0 if we reach this func)*/
        const int rc = (wr == toSend && *p_max_bytes > 0) ? 0 : -3;
        chunkqueue_mark_written(cq, wr);
        return rc;
    }
    else
        return network_write_error(fd, errh);
}




/* write next chunk(s); finished chunks are removed afterwards after successful writes.
 * return values: similar as backends (0 success, -1 error, -2 remote close, -3 try again later (EINTR/EAGAIN)) */
/* next chunk must be MEM_CHUNK. use write()/send() */
#if !defined(NETWORK_WRITE_USE_WRITEV)
static int network_write_mem_chunk(const int fd, chunkqueue * const cq, off_t * const p_max_bytes, log_error_st * const errh) {
    chunk* const c = cq->first;
    off_t c_len = (off_t)buffer_clen(c->mem) - c->offset;
    if (c_len > *p_max_bytes) c_len = *p_max_bytes;
    if (c_len <= 0) return network_remove_finished_chunks(cq, c_len);

    ssize_t wr = network_write_data_len(fd, c->mem->ptr + c->offset, c_len);
    return network_write_accounting(fd, cq, p_max_bytes, errh, wr, c_len);
}
#endif




__attribute_noinline__
static int network_write_file_chunk_no_mmap(const int fd, chunkqueue * const cq, off_t * const p_max_bytes, log_error_st * const errh) {
    chunk* const c = cq->first;
    off_t toSend = c->file.length - c->offset;
    char buf[16384]; /* max read 16kb in one step */

    if (toSend > *p_max_bytes) toSend = *p_max_bytes;
    if (toSend <= 0) return network_remove_finished_chunks(cq, toSend);
    if (toSend > (off_t)sizeof(buf)) toSend = (off_t)sizeof(buf);

    if (c->file.fd < 0 && 0 != chunkqueue_open_file_chunk(cq, errh)) return -1;

    toSend = chunk_file_pread(c->file.fd, buf, toSend, c->offset);
    if (toSend <= 0) {
        log_perror(errh, __FILE__, __LINE__, "read");/* err or unexpected EOF */
        return -1;
    }

    ssize_t wr = network_write_data_len(fd, buf, toSend);
    return network_write_accounting(fd, cq, p_max_bytes, errh, wr, toSend);
}




#if defined(NETWORK_WRITE_USE_MMAP)

#include "sys-setjmp.h"

static off_t
network_write_setjmp_write_cb (void *fd, const void *data, off_t len)
{
    return network_write_data_len((int)(uintptr_t)fd, data, len);
}

/* next chunk must be FILE_CHUNK. send mmap()ed file with write() */
static int network_write_file_chunk_mmap(const int fd, chunkqueue * const cq, off_t * const p_max_bytes, log_error_st * const errh) {
    chunk * const restrict c = cq->first;
    const chunk_file_view * const restrict cfv = (!c->file.is_temp)
      ? chunkqueue_chunk_file_view(cq->first, 0, errh)/*use default 512k block*/
      : NULL;
    if (NULL == cfv)
        return network_write_file_chunk_no_mmap(fd, cq, p_max_bytes, errh);

    off_t toSend = c->file.length - c->offset;
    if (toSend > *p_max_bytes) toSend = *p_max_bytes;
    if (toSend <= 0) return network_remove_finished_chunks(cq, toSend);

    const off_t mmap_avail = chunk_file_view_dlen(cfv, c->offset);
    const char * const data = chunk_file_view_dptr(cfv, c->offset);
    if (toSend > mmap_avail) toSend = mmap_avail;
    off_t wr = sys_setjmp_eval3(network_write_setjmp_write_cb,
                                (void *)(uintptr_t)fd, data, toSend);
    return network_write_accounting(fd,cq,p_max_bytes,errh,(ssize_t)wr,toSend);
}

#endif /* NETWORK_WRITE_USE_MMAP */




#if defined(NETWORK_WRITE_USE_WRITEV)

#if defined(HAVE_SYS_UIO_H)
# include <sys/uio.h>
#endif

#if defined(UIO_MAXIOV)
# define SYS_MAX_CHUNKS UIO_MAXIOV
#elif defined(IOV_MAX)
/* new name for UIO_MAXIOV since IEEE Std 1003.1-2001 */
# define SYS_MAX_CHUNKS IOV_MAX
#elif defined(_XOPEN_IOV_MAX)
/* minimum value for sysconf(_SC_IOV_MAX); posix requires this to be at least 16, which is good enough - no need to call sysconf() */
# define SYS_MAX_CHUNKS _XOPEN_IOV_MAX
#else
# error neither UIO_MAXIOV nor IOV_MAX nor _XOPEN_IOV_MAX are defined
#endif

/* allocate iovec[MAX_CHUNKS] on stack, so pick a sane limit:
 * - each entry will use 1 pointer + 1 size_t
 * - 32 chunks -> 256 / 512 bytes (32-bit/64-bit pointers)
 */
#define STACK_MAX_ALLOC_CHUNKS 32
#if SYS_MAX_CHUNKS > STACK_MAX_ALLOC_CHUNKS
# define MAX_CHUNKS STACK_MAX_ALLOC_CHUNKS
#else
# define MAX_CHUNKS SYS_MAX_CHUNKS
#endif

/* next chunk must be MEM_CHUNK. send multiple mem chunks using writev() */
static int network_writev_mem_chunks(const int fd, chunkqueue * const cq, off_t * const p_max_bytes, log_error_st * const errh) {
    size_t num_chunks = 0;
    off_t toSend = 0;
    struct iovec chunks[MAX_CHUNKS];

    for (const chunk *c = cq->first; c && MEM_CHUNK == c->type; c = c->next) {
        const off_t c_len = (off_t)buffer_clen(c->mem) - c->offset;
        if (c_len > 0) {
            toSend += c_len;

            chunks[num_chunks].iov_base = c->mem->ptr + c->offset;
            chunks[num_chunks].iov_len = (size_t)c_len;

            if (++num_chunks == MAX_CHUNKS || toSend >= *p_max_bytes) break;
        }
        else if (c_len < 0) /*(should not happen; trigger assert)*/
            return network_remove_finished_chunks(cq, c_len);
    }
    if (0 == num_chunks) return network_remove_finished_chunks(cq, 0);

    ssize_t wr = writev(fd, chunks, num_chunks);
    return network_write_accounting(fd, cq, p_max_bytes, errh, wr, toSend);
}

#endif /* NETWORK_WRITE_USE_WRITEV */




#if defined(NETWORK_WRITE_USE_SENDFILE)

#if defined(NETWORK_WRITE_USE_LINUX_SENDFILE) \
 || defined(NETWORK_WRITE_USE_SOLARIS_SENDFILEV)
#include <sys/sendfile.h>
#endif

#if defined(NETWORK_WRITE_USE_FREEBSD_SENDFILE) \
 || defined(NETWORK_WRITE_USE_DARWIN_SENDFILE)
#include <sys/uio.h>
#endif

static int network_write_file_chunk_sendfile(const int fd, chunkqueue * const cq, off_t * const p_max_bytes, log_error_st * const errh) {
    chunk * const c = cq->first;
    ssize_t wr;
    off_t offset;
    off_t toSend;
    off_t written = 0;

    offset = c->offset;
    toSend = c->file.length - c->offset;
    if (toSend > *p_max_bytes) toSend = *p_max_bytes;
    if (toSend <= 0) return network_remove_finished_chunks(cq, toSend);

    if (c->file.fd < 0 && 0 != chunkqueue_open_file_chunk(cq, errh)) return -1;

    /* Darwin, FreeBSD, and Solaris variants support iovecs and could
     * be optimized to send more than just file in single syscall */

  #if defined(NETWORK_WRITE_USE_LINUX_SENDFILE)

    wr = sendfile(fd, c->file.fd, &offset, toSend);
    if (wr > 0) written = (off_t)wr;

  #elif defined(NETWORK_WRITE_USE_DARWIN_SENDFILE)

    written = toSend;
    wr = sendfile(c->file.fd, fd, offset, &written, NULL, 0);
    /* (for EAGAIN/EINTR written still contains the sent bytes) */

  #elif defined(NETWORK_WRITE_USE_FREEBSD_SENDFILE)

    wr = sendfile(c->file.fd, fd, offset, toSend, NULL, &written, 0);
    /* (for EAGAIN/EINTR written still contains the sent bytes) */

  #elif defined(NETWORK_WRITE_USE_SOLARIS_SENDFILEV)
    {
        sendfilevec_t fvec;
        fvec.sfv_fd = c->file.fd;
        fvec.sfv_flag = 0;
        fvec.sfv_off = offset;
        fvec.sfv_len = toSend;

        /* Solaris sendfilev() */
        wr = sendfilev(fd, &fvec, 1, (size_t *)&written);
        /* (for EAGAIN/EINTR written still contains the sent bytes) */
    }
  #else

    wr = -1;
    errno = ENOSYS;

  #endif

    if (-1 == wr) {
        switch(errno) {
          case EAGAIN:
          case EINTR:
            break; /* try again later */
          case EPIPE:
          case ECONNRESET:
          case ENOTCONN:
            return -2;
          case EINVAL:
          case ENOSYS:
         #if defined(ENOTSUP) && (!defined(EOPNOTSUPP) || EOPNOTSUPP != ENOTSUP)
          case ENOTSUP:
         #endif
         #ifdef EOPNOTSUPP
          case EOPNOTSUPP:
         #endif
         #ifdef ESOCKTNOSUPPORT
          case ESOCKTNOSUPPORT:
         #endif
         #ifdef EAFNOSUPPORT
          case EAFNOSUPPORT:
         #endif
           #ifdef NETWORK_WRITE_USE_MMAP
            return network_write_file_chunk_mmap(fd, cq, p_max_bytes, errh);
           #else
            return network_write_file_chunk_no_mmap(fd, cq, p_max_bytes, errh);
           #endif
          default:
            log_perror(errh, __FILE__, __LINE__, "sendfile(): fd: %d", fd);
            return -1;
        }
    }

    if (written > 0) {
        chunkqueue_mark_written(cq, written);
        *p_max_bytes -= written;
        if (__builtin_expect( (*p_max_bytes <= 0), 0)) return -3;
    }
    else if (0 == wr) { /*(-1 != wr && 0 == written)*/
        log_error(errh, __FILE__, __LINE__,
                  "sendfile(): fd: %d file truncated", fd);
        return -1;
    }

    return (wr >= 0 && written == toSend) ? 0 : -3;
}

#endif




/* return values:
 * >= 0 : no error
 *   -1 : error (on our side)
 *   -2 : remote close
 */

static int network_write_chunkqueue_writev(const int fd, chunkqueue * const cq, off_t max_bytes, log_error_st * const errh) {
    while (NULL != cq->first) {
        int rc = -1;

        switch (cq->first->type) {
        case MEM_CHUNK:
          #if defined(NETWORK_WRITE_USE_WRITEV)
            rc = network_writev_mem_chunks(fd, cq, &max_bytes, errh);
          #else
            rc = network_write_mem_chunk(fd, cq, &max_bytes, errh);
          #endif
            break;
        case FILE_CHUNK:
          #ifdef NETWORK_WRITE_USE_MMAP
            rc = network_write_file_chunk_mmap(fd, cq, &max_bytes, errh);
          #else
            rc = network_write_file_chunk_no_mmap(fd, cq, &max_bytes, errh);
          #endif
            break;
        }

        if (__builtin_expect( (0 != rc), 0)) return (-3 == rc) ? 0 : rc;
    }

    return 0;
}

#if defined(NETWORK_WRITE_USE_SENDFILE)
static int network_write_chunkqueue_sendfile(const int fd, chunkqueue * const cq, off_t max_bytes, log_error_st * const errh) {
    while (NULL != cq->first) {
        int rc = -1;

        switch (cq->first->type) {
        case MEM_CHUNK:
          #if defined(NETWORK_WRITE_USE_WRITEV)
            rc = network_writev_mem_chunks(fd, cq, &max_bytes, errh);
          #else
            rc = network_write_mem_chunk(fd, cq, &max_bytes, errh);
          #endif
            break;
        case FILE_CHUNK:
          #if defined(NETWORK_WRITE_USE_SENDFILE)
            rc = network_write_file_chunk_sendfile(fd, cq, &max_bytes, errh);
          #elif defined(NETWORK_WRITE_USE_MMAP)
            rc = network_write_file_chunk_mmap(fd, cq, &max_bytes, errh);
          #else
            rc = network_write_file_chunk_no_mmap(fd, cq, &max_bytes, errh);
          #endif
            break;
        }

        if (__builtin_expect( (0 != rc), 0)) return (-3 == rc) ? 0 : rc;
    }

    return 0;
}
#endif

int network_write_init(server *srv) {
    typedef enum {
        NETWORK_BACKEND_UNSET,
        NETWORK_BACKEND_WRITE,
        NETWORK_BACKEND_WRITEV,
        NETWORK_BACKEND_SENDFILE,
    } network_backend_t;

    network_backend_t backend;

    struct nb_map {
        network_backend_t nb;
        const char *name;
    } network_backends[] = {
        /* lowest id wins */
        { NETWORK_BACKEND_SENDFILE, "sendfile" },
        { NETWORK_BACKEND_SENDFILE, "linux-sendfile" },
        { NETWORK_BACKEND_SENDFILE, "freebsd-sendfile" },
        { NETWORK_BACKEND_SENDFILE, "solaris-sendfilev" },
        { NETWORK_BACKEND_WRITEV,   "writev" },
        { NETWORK_BACKEND_WRITE,    "write" },
        { NETWORK_BACKEND_UNSET,    NULL }
    };

    /* get a useful default */
    backend = network_backends[0].nb;

    /* match name against known types */
    if (srv->srvconf.network_backend) {
        const char *name, *confname = srv->srvconf.network_backend->ptr;
        for (size_t i = 0; NULL != (name = network_backends[i].name); ++i) {
            if (0 == strcmp(confname, name)) {
                backend = network_backends[i].nb;
                break;
            }
        }
        if (NULL == name) {
            log_error(srv->errh, __FILE__, __LINE__,
              "server.network-backend has an unknown value: %s", confname);
            return -1;
        }
    }

    switch(backend) {
    case NETWORK_BACKEND_SENDFILE:
      #if defined(NETWORK_WRITE_USE_SENDFILE)
        srv->network_backend_write = network_write_chunkqueue_sendfile;
        break;
      #endif
    case NETWORK_BACKEND_WRITEV:
    case NETWORK_BACKEND_WRITE:
        srv->network_backend_write = network_write_chunkqueue_writev;
        break;
    default:
        return -1;
    }

    return 0;
}

const char * network_write_show_handlers(void) {
    return
      "\nNetwork handler:\n\n"
     #if defined NETWORK_WRITE_USE_LINUX_SENDFILE
      "\t+ linux-sendfile\n"
     #else
      "\t- linux-sendfile\n"
     #endif
     #if defined NETWORK_WRITE_USE_FREEBSD_SENDFILE
      "\t+ freebsd-sendfile\n"
     #else
      "\t- freebsd-sendfile\n"
     #endif
     #if defined NETWORK_WRITE_USE_DARWIN_SENDFILE
      "\t+ darwin-sendfile\n"
     #else
      "\t- darwin-sendfile\n"
     #endif
     #if defined NETWORK_WRITE_USE_SOLARIS_SENDFILEV
      "\t+ solaris-sendfilev\n"
     #else
      "\t- solaris-sendfilev\n"
     #endif
     #if defined NETWORK_WRITE_USE_WRITEV
      "\t+ writev\n"
     #else
      "\t- writev\n"
     #endif
      "\t+ write\n"
     #ifdef NETWORK_WRITE_USE_MMAP
      "\t+ mmap support\n"
     #else
      "\t- mmap support\n"
     #endif
      ;
}
