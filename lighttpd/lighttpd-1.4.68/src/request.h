#ifndef _REQUEST_H_
#define _REQUEST_H_
#include "first.h"

#include "sys-time.h"   /* (struct timespec) */

#include "base_decls.h"
#include "buffer.h"
#include "array.h"
#include "chunk.h"
#include "http_kv.h"

struct chunkqueue;      /* declaration */
struct cond_cache_t;    /* declaration */
struct cond_match_t;    /* declaration */
struct stat_cache_entry;/* declaration */

typedef struct request_config {
    fdlog_st *errh;
    unsigned int http_parseopts;
    uint32_t max_request_field_size;
    const array *mimetypes;

    /* virtual-servers */
    const buffer *document_root;
    const buffer *server_name;
    const buffer *server_tag;

    unsigned int max_request_size;
    unsigned short max_keep_alive_requests;
    unsigned short max_keep_alive_idle;
    unsigned short max_read_idle;
    unsigned short max_write_idle;
    unsigned short stream_request_body;
    unsigned short stream_response_body;
    unsigned int high_precision_timestamps:1;
    unsigned int allow_http11:1;
    unsigned int range_requests:1;
    unsigned int follow_symlink:1;
    unsigned int etag_flags:3;
    unsigned int use_xattr:1;
    unsigned int force_lowercase_filenames:2;/*(case-insensitive file systems)*/
    unsigned int error_intercept:1;

    unsigned int h2proto:2; /*(global setting copied for convenient access)*/

    /* debug */
    unsigned int log_request_handling:1;
    unsigned int log_state_handling:1;
    unsigned int log_condition_handling:1;
    unsigned int log_response_header:1;
    unsigned int log_request_header:1;
    unsigned int log_request_header_on_error:1;
    unsigned int log_file_not_found:1;
    unsigned int log_timeouts:1;

    unsigned int bytes_per_second; /* connection bytes/sec limit */
    unsigned int global_bytes_per_second;/*total bytes/sec limit for scope*/

    /* server-wide traffic-shaper
     *
     * each context has the counter which is inited once
     * a second by the global_bytes_per_second config-var
     *
     * as soon as global_bytes_per_second gets below 0
     * the connected conns are "offline" a little bit
     *
     * the problem:
     * we somehow have to lose our "we are writable" signal on the way.
     *
     */
    off_t *global_bytes_per_second_cnt_ptr; /*  */

    const buffer *error_handler;
    const buffer *error_handler_404;
    const buffer *errorfile_prefix;
    fdlog_st *serrh; /* script errh */
} request_config;

typedef struct {
    buffer scheme; /* scheme without colon or slashes ( "http" or "https" ) */

    /* authority with optional portnumber ("site.name" or "site.name:8080" ) NOTE: without "username:password@" */
    buffer authority;

    /* path including leading slash ("/" or "/index.html") - urldecoded, and sanitized  ( buffer_path_simplify() && buffer_urldecode_path() ) */
    buffer path;
    buffer query; /* querystring ( everything after "?", ie: in "/index.php?foo=1", query is "foo=1" ) */
} request_uri;

typedef struct {
    buffer path;
    buffer basedir; /* path = "(basedir)(.*)" */

    buffer doc_root; /* path = doc_root + rel_path */
    buffer rel_path;
} physical;

typedef struct {
    off_t gw_chunked;
    buffer b;
    int done;
} response_dechunk;

/* the order of the items should be the same as they are processed
 * read before write as we use this later e.g. <= CON_STATE_REQUEST_END */
/* NB: must sync with http_request_state_short(), http_request_state_append() */
typedef enum {
    CON_STATE_CONNECT,
    CON_STATE_REQUEST_START,
    CON_STATE_READ,
    CON_STATE_REQUEST_END,
    CON_STATE_READ_POST,
    CON_STATE_HANDLE_REQUEST,
    CON_STATE_RESPONSE_START,
    CON_STATE_WRITE,
    CON_STATE_RESPONSE_END,
    CON_STATE_ERROR,
    CON_STATE_CLOSE
} request_state_t;

struct request_st {
    request_state_t state; /*(modules should not modify request state)*/
    int http_status;
    uint32_t h2state;      /*(modules should not modify request h2state)*/
    uint32_t h2id;
     int32_t h2_rwin;
     int32_t h2_swin;
     int16_t h2_rwin_fudge;
     uint8_t h2_prio;

    http_method_t http_method;
    http_version_t http_version;

    const plugin *handler_module;
    void **plugin_ctx;           /* plugin connection specific config */
    connection *con;

    /* config conditions (internal) */
    uint32_t conditional_is_valid;
    struct cond_cache_t *cond_cache;
    struct cond_match_t **cond_match;
    struct cond_match_t *cond_match_data;

    request_config conf;

    /* request */
    uint32_t rqst_header_len;
    uint64_t rqst_htags;/* bitfield of flagged headers present in request */
    array rqst_headers;

    request_uri uri;
    physical physical;
    array env; /* used to pass lighttpd internal stuff */

    off_t reqbody_length; /* request Content-Length */
    off_t te_chunked;
    off_t resp_body_scratchpad;

    buffer *http_host; /* copy of array value buffer ptr; not alloc'ed */
    const buffer *server_name;

    buffer target;
    buffer target_orig;

    buffer pathinfo;
    buffer server_name_buf;

    /* response */
    uint32_t resp_header_len;
    uint64_t resp_htags; /*bitfield of flagged headers present in response*/
    array resp_headers;
    char resp_body_finished;
    char resp_body_started;
    char resp_send_chunked;
    char resp_decode_chunked;
    char resp_header_repeated;

    char loops_per_request;  /* catch endless loops in a single request */
    int8_t keep_alive; /* only request.c can enable it, all other just disable */
    char async_callback;

    buffer *tmp_buf;                    /* shared; same as srv->tmp_buf */
    response_dechunk *gw_dechunk;

    off_t bytes_written_ckpt; /* used by mod_accesslog */
    off_t bytes_read_ckpt;    /* used by mod_accesslog */
    unix_timespec64_t start_hp;

    int error_handler_saved_status; /* error-handler */
    http_method_t error_handler_saved_method; /* error-handler */

    struct chunkqueue write_queue;     /* HTTP response queue [ file, mem ] */
    struct chunkqueue read_queue;      /* HTTP request queue  [ mem ] */
    struct chunkqueue reqbody_queue; /*(might use tempfiles)*/

    struct stat_cache_entry *tmp_sce; /*(value valid only in sequential code)*/
    int cond_captures;
    int h2_connect_ext;
};


typedef struct http_header_parse_ctx {
    char *k;
    char *v;
    uint32_t klen;
    uint32_t vlen;
    uint32_t hlen;
    uint8_t pseudo;
    uint8_t scheme;
    uint8_t trailers;
    int8_t id;
    uint32_t max_request_field_size;
    unsigned int http_parseopts;
} http_header_parse_ctx;


int http_request_validate_pseudohdrs (request_st * restrict r, int scheme, unsigned int http_parseopts);
int http_request_parse_header (request_st * restrict r, http_header_parse_ctx * restrict hpctx);
void http_request_headers_process_h2 (request_st * restrict r, int scheme_port);
void http_request_headers_process (request_st * restrict r, char * restrict hdrs, const unsigned short * restrict hoff, int scheme_port);
int http_request_parse_target(request_st *r, int scheme_port);
int http_request_host_normalize(buffer *b, int scheme_port);
int http_request_host_policy(buffer *b, unsigned int http_parseopts, int scheme_port);

int64_t li_restricted_strtoint64 (const char *v, const uint32_t vlen, const char ** const err);


/* convenience macros/functions for display purposes */

#define http_request_state_is_keep_alive(r) \
  (CON_STATE_READ == (r)->state && !buffer_is_blank(&(r)->target_orig))

#define http_con_state_is_keep_alive(con) \
  ((con)->h2                              \
   ? 0 == (con)->h2->rused                \
   : http_request_state_is_keep_alive(&(con)->request))

#define http_con_state_append(b, con)                            \
   (http_con_state_is_keep_alive(con)                            \
    ? buffer_append_string_len((b), CONST_STR_LEN("keep-alive")) \
    : http_request_state_append((b), (con)->request.state))

#define http_con_state_short(con)     \
   (http_con_state_is_keep_alive(con) \
    ? "k"                             \
    : http_request_state_short((con)->request.state))

#define http_request_stats_bytes_in(r) \
   ((r)->read_queue.bytes_out - (r)->bytes_read_ckpt)

#define http_request_stats_bytes_out(r) \
   ((r)->write_queue.bytes_out - (r)->bytes_written_ckpt)

__attribute_pure__
const char * http_request_state_short (request_state_t state);

void http_request_state_append (buffer *b, request_state_t state);


#endif
