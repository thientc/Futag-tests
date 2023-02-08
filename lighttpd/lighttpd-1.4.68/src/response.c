#include "first.h"

#include "response.h"
#include "request.h"
#include "reqpool.h"
#include "base.h"
#include "fdevent.h"
#include "http_header.h"
#include "http_kv.h"
#include "log.h"
#include "stat_cache.h"
#include "chunk.h"
#include "http_chunk.h"
#include "http_date.h"
#include "http_range.h"

#include "plugin.h"
#include "plugins.h"

#include <sys/types.h>
#include <sys/stat.h>
#include "sys-time.h"

#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


__attribute_cold__
void
http_response_delay (connection * const con)
{
    if (config_feature_bool(con->srv, "auth.delay-invalid-creds", 1)){
        /*(delay sending response)*/
        con->is_writable = 0;
        con->traffic_limit_reached = 1;
    }
}


int
http_response_omit_header (request_st * const r, const data_string * const ds)
{
    const size_t klen = buffer_clen(&ds->key);
    if (klen == sizeof("X-Sendfile")-1
        && buffer_eq_icase_ssn(ds->key.ptr, CONST_STR_LEN("X-Sendfile")))
        return 1;
    if (klen >= sizeof("X-LIGHTTPD-")-1
        && buffer_eq_icase_ssn(ds->key.ptr, CONST_STR_LEN("X-LIGHTTPD-"))) {
        if (klen == sizeof("X-LIGHTTPD-KBytes-per-second")-1
            && buffer_eq_icase_ssn(ds->key.ptr+sizeof("X-LIGHTTPD-")-1,
                                   CONST_STR_LEN("KBytes-per-second"))) {
            /* "X-LIGHTTPD-KBytes-per-second" */
            off_t limit = strtol(ds->value.ptr, NULL, 10) << 10; /*(*=1024)*/
            if (limit > 0
                && (limit < r->conf.bytes_per_second
                    || 0 == r->conf.bytes_per_second)) {
                r->conf.bytes_per_second = limit;
            }
        }
        return 1;
    }
    return 0;
}


__attribute_cold__
static void
http_response_write_header_partial_1xx (request_st * const r, buffer * const b)
{
    /* take data in con->write_queue and move into b
     * (to be sent prior to final response headers in r->write_queue) */
    connection * const con = r->con;
    /*assert(&r->write_queue != con->write_queue);*/
    chunkqueue * const cq = con->write_queue;
    con->write_queue = &r->write_queue;

    /*assert(0 == buffer_clen(b));*//*expect empty buffer from caller*/
    uint32_t len = (uint32_t)chunkqueue_length(cq);
    /*(expecting MEM_CHUNK(s), so not expecting error reading files)*/
    if (chunkqueue_read_data(cq, buffer_string_prepare_append(b, len),
                             len, r->conf.errh) < 0)
        len = 0;
    buffer_truncate(b, len);/*expect initial empty buffer from caller*/
    chunkqueue_free(cq);
}


void
http_response_write_header (request_st * const r)
{
	/* disable keep-alive if requested */

	r->con->keep_alive_idle = r->conf.max_keep_alive_idle;
	if (__builtin_expect( (0 == r->conf.max_keep_alive_idle), 0)
	    || r->con->request_count > r->conf.max_keep_alive_requests) {
		r->keep_alive = 0;
	} else if (0 != r->reqbody_length
		   && r->reqbody_length != r->reqbody_queue.bytes_in
		   && (NULL == r->handler_module
		       || 0 == (r->conf.stream_request_body
		                & (FDEVENT_STREAM_REQUEST
		                   | FDEVENT_STREAM_REQUEST_BUFMIN)))) {
		r->keep_alive = 0;
	}

	if (light_btst(r->resp_htags, HTTP_HEADER_UPGRADE)
	    && r->http_version == HTTP_VERSION_1_1) {
		http_header_response_set(r, HTTP_HEADER_CONNECTION, CONST_STR_LEN("Connection"), CONST_STR_LEN("upgrade"));
	} else if (r->keep_alive <= 0) {
		if (r->keep_alive < 0)
			http_response_delay(r->con);
		http_header_response_set(r, HTTP_HEADER_CONNECTION, CONST_STR_LEN("Connection"), CONST_STR_LEN("close"));
	} else if (r->http_version == HTTP_VERSION_1_0) {/*(&& r->keep_alive > 0)*/
		http_header_response_set(r, HTTP_HEADER_CONNECTION, CONST_STR_LEN("Connection"), CONST_STR_LEN("keep-alive"));
	}

	if (304 == r->http_status
	    && light_btst(r->resp_htags, HTTP_HEADER_CONTENT_ENCODING)) {
		http_header_response_unset(r, HTTP_HEADER_CONTENT_ENCODING, CONST_STR_LEN("Content-Encoding"));
	}

	chunkqueue * const cq = &r->write_queue;
	buffer * const b = chunkqueue_prepend_buffer_open(cq);

	if (cq != r->con->write_queue)
		http_response_write_header_partial_1xx(r, b);

	buffer_append_string_len(b,
	                         (r->http_version == HTTP_VERSION_1_1)
	                           ? "HTTP/1.1 "
	                           : "HTTP/1.0 ",
	                         sizeof("HTTP/1.1 ")-1);
	http_status_append(b, r->http_status);

	/* add all headers */
	for (size_t i = 0, used = r->resp_headers.used; i < used; ++i) {
		const data_string * const ds = (data_string *)r->resp_headers.data[i];
		const uint32_t klen = buffer_clen(&ds->key);
		const uint32_t vlen = buffer_clen(&ds->value);
		if (__builtin_expect( (0 == klen), 0)) continue;
		if (__builtin_expect( (0 == vlen), 0)) continue;
		if ((ds->key.ptr[0] & 0xdf) == 'X' && http_response_omit_header(r, ds))
			continue;
		char * restrict s = buffer_extend(b, klen+vlen+4);
		s[0] = '\r';
		s[1] = '\n';
		memcpy(s+2, ds->key.ptr, klen);
		s += 2+klen;
		s[0] = ':';
		s[1] = ' ';
		memcpy(s+2, ds->value.ptr, vlen);
	}

	if (!light_btst(r->resp_htags, HTTP_HEADER_DATE)) {
		/* HTTP/1.1 and later requires a Date: header */
		/* "\r\nDate: " 8-chars + 30-chars "%a, %d %b %Y %T GMT" + '\0' */
		static unix_time64_t tlast = 0;
		static char tstr[40] = "\r\nDate: ";

		/* cache the generated timestamp */
		const unix_time64_t cur_ts = log_epoch_secs;
		if (__builtin_expect ( (tlast != cur_ts), 0))
			http_date_time_to_str(tstr+8, sizeof(tstr)-8, (tlast = cur_ts));

		buffer_append_string_len(b, tstr, 37);
	}

	if (!light_btst(r->resp_htags, HTTP_HEADER_SERVER) && r->conf.server_tag)
		buffer_append_str2(b, CONST_STR_LEN("\r\nServer: "),
		                      BUF_PTR_LEN(r->conf.server_tag));

	buffer_append_string_len(b, CONST_STR_LEN("\r\n\r\n"));

	r->resp_header_len = buffer_clen(b);

	if (r->conf.log_response_header) {
		log_error_multiline(r->conf.errh, __FILE__, __LINE__,
		                    BUF_PTR_LEN(b), "fd:%d resp: ", r->con->fd);
	}

	chunkqueue_prepend_buffer_commit(cq);

	/*(optimization to use fewer syscalls to send a small response)*/
	off_t cqlen;
	if (r->resp_body_finished
	    && light_btst(r->resp_htags, HTTP_HEADER_CONTENT_LENGTH)
	    && (cqlen = chunkqueue_length(cq) - r->resp_header_len) > 0
	    && cqlen < 16384)
		chunkqueue_small_resp_optim(cq);
}


__attribute_cold__
static handler_t
http_response_physical_path_error (request_st * const r, const int code, const char * const msg)
{
    r->http_status = code;
    if ((code == 404 && r->conf.log_file_not_found)
        || r->conf.log_request_handling) {
        if (NULL == msg)
            log_perror(r->conf.errh, __FILE__, __LINE__, "-- ");
        else
            log_error(r->conf.errh, __FILE__, __LINE__, "%s", msg);
        log_error(r->conf.errh, __FILE__, __LINE__,
          "Path         : %s", r->physical.path.ptr);
        log_error(r->conf.errh, __FILE__, __LINE__,
          "URI          : %s", r->uri.path.ptr);
    }
    return HANDLER_FINISHED;
}


static handler_t http_response_physical_path_check(request_st * const r) {
	stat_cache_entry *sce = stat_cache_get_entry(&r->physical.path);

	if (__builtin_expect( (sce != NULL), 1)) {
		/* file exists */
	} else {
		switch (errno) {
		case ENOTDIR:
			/* PATH_INFO ! :) */
			break;
		case EACCES:
			return http_response_physical_path_error(r, 403, NULL);
		case ENAMETOOLONG:
			/* file name to be read was too long. return 404 */
		case ENOENT:
			if (r->http_method == HTTP_METHOD_OPTIONS
			    && light_btst(r->resp_htags, HTTP_HEADER_ALLOW)) {
				r->http_status = 200;
				return HANDLER_FINISHED;
			}
			return http_response_physical_path_error(r, 404, NULL);
		default:
			/* we have no idea what happened. let's tell the user so. */
			return http_response_physical_path_error(r, 500, NULL);
		}

		/* not found, perhaps PATHINFO */

		char *pathinfo;
		{
			/*(might check at startup that s->document_root does not end in '/')*/
			size_t len = buffer_clen(&r->physical.basedir)
			           - (buffer_has_pathsep_suffix(&r->physical.basedir));
			pathinfo = r->physical.path.ptr + len;
			if ('/' != *pathinfo) {
				pathinfo = NULL;
			}
			else if (pathinfo == r->physical.path.ptr) { /*(basedir is "/")*/
				pathinfo = strchr(pathinfo+1, '/');
			}
		}

		const uint32_t pathused = r->physical.path.used;
		for (char *pprev = pathinfo; pathinfo; pprev = pathinfo, pathinfo = strchr(pathinfo+1, '/')) {
			/*(temporarily modify r->physical.path in-place)*/
			r->physical.path.used = pathinfo - r->physical.path.ptr + 1;
			*pathinfo = '\0';
			stat_cache_entry * const nsce = stat_cache_get_entry(&r->physical.path);
			*pathinfo = '/';
			r->physical.path.used = pathused;
			if (NULL == nsce) {
				pathinfo = pathinfo != pprev ? pprev : NULL;
				break;
			}
			sce = nsce;
			if (!S_ISDIR(sce->st.st_mode)) break;
		}

		if (NULL == pathinfo || !S_ISREG(sce->st.st_mode)) {
			/* no it really doesn't exists */
			return http_response_physical_path_error(r, 404, "-- file not found");
		}
		/* note: historical behavior checks S_ISREG() above, permitting
		 * path-info only on regular files, not dirs or special files */

		/* we have a PATHINFO */
		if (pathinfo) {
			size_t len = r->physical.path.ptr+pathused-1-pathinfo, reqlen;
			if (r->conf.force_lowercase_filenames
			    && len <= (reqlen = buffer_clen(&r->target))
			    && buffer_eq_icase_ssn(r->target.ptr + reqlen - len, pathinfo, len)) {
				/* attempt to preserve case-insensitive PATH_INFO
				 * (works in common case where mod_alias, mod_magnet, and other modules
				 *  have not modified the PATH_INFO portion of request URI, or did so
				 *  with exactly the PATH_INFO desired) */
				buffer_copy_string_len(&r->pathinfo, r->target.ptr + reqlen - len, len);
			} else {
				buffer_copy_string_len(&r->pathinfo, pathinfo, len);
			}

			/*
			 * shorten uri.path
			 */

			buffer_truncate(&r->uri.path, buffer_clen(&r->uri.path) - len);
			buffer_truncate(&r->physical.path, (size_t)(pathinfo - r->physical.path.ptr));
		}
	}

	if (!r->conf.follow_symlink
	    && 0 != stat_cache_path_contains_symlink(&r->physical.path, r->conf.errh)) {
		return http_response_physical_path_error(r, 403, "-- access denied due to symlink restriction");
	}

	/* r->tmp_sce is valid in handle_subrequest_start callback --
	 * handle_subrquest_start callbacks should not change r->physical.path
	 * (or should invalidate r->tmp_sce).  r->tmp_sce is not reset between
	 * requests and is valid only for sequential code after this func succeeds*/
	r->tmp_sce = sce;

	if (S_ISREG(sce->st.st_mode)) /*(common case)*/
		return HANDLER_GO_ON;

	if (S_ISDIR(sce->st.st_mode)) {
		if (!buffer_has_slash_suffix(&r->uri.path)) {
			http_response_redirect_to_directory(r, 301);
			return HANDLER_FINISHED;
		}
	} else {
		/* any special handling of other non-reg files ?*/
	}

	return HANDLER_GO_ON;
}

__attribute_cold__
__attribute_noinline__
static handler_t http_status_set_error_close (request_st * const r, int status) {
    r->keep_alive = 0;
    r->resp_body_finished = 1;
    r->handler_module = NULL;
    r->http_status = status;
    return HANDLER_FINISHED;
}

__attribute_cold__
static handler_t http_response_prepare_options_star (request_st * const r) {
    r->http_status = 200;
    r->resp_body_finished = 1;
    http_header_response_append(r, HTTP_HEADER_ALLOW, CONST_STR_LEN("Allow"),
                                CONST_STR_LEN("OPTIONS, GET, HEAD, POST"));
    return HANDLER_FINISHED;
}


__attribute_cold__
static handler_t http_response_prepare_connect (request_st * const r) {
    return (r->handler_module)
      ? HANDLER_GO_ON
      : http_status_set_error_close(r, 405);/* 405 Method Not Allowed */
}


static handler_t http_response_config (request_st * const r) {
    config_cond_cache_reset(r);
    config_patch_config(r);

    r->server_name = r->conf.server_name
                   ? r->conf.server_name
                   : &r->uri.authority;

    /* do we have to downgrade from 1.1 to 1.0 ? (ignore for HTTP/2) */
    if (__builtin_expect( (!r->conf.allow_http11), 0)
        && r->http_version == HTTP_VERSION_1_1) {
        r->http_version = HTTP_VERSION_1_0;
        /*(when forcing HTTP/1.0, ignore (unlikely) Connection: keep-alive)*/
        r->keep_alive = 0;
    }

    if (__builtin_expect( (r->reqbody_length > 0), 0)
        && 0 != r->conf.max_request_size   /* r->conf.max_request_size in kB */
        && (off_t)r->reqbody_length > ((off_t)r->conf.max_request_size << 10)) {
        log_error(r->conf.errh, __FILE__, __LINE__,
          "request-size too long: %lld -> 413", (long long) r->reqbody_length);
        return /* 413 Payload Too Large */
          http_status_set_error_close(r, 413);
    }

    return HANDLER_GO_ON;
}


__attribute_noinline__
static handler_t
http_response_prepare (request_st * const r)
{
    handler_t rc;

	/* looks like someone has already made a decision */
	if (__builtin_expect( (r->http_status > 200), 0)) { /* yes, > 200 */
		if (0 == r->resp_body_finished)
			http_response_body_clear(r, 0);
		return HANDLER_FINISHED;
	}

	/* no decision yet, build conf->filename */
	if (buffer_is_unset(&r->physical.path)) {

		if (__builtin_expect( (!r->async_callback), 1)) {
			rc = http_response_config(r);
			if (HANDLER_GO_ON != rc) return rc;
		}
		else
			r->async_callback = 0; /* reset */

		/* we only come here when we have the parse the full request again
		 *
		 * a HANDLER_COMEBACK from mod_rewrite and mod_fastcgi might be a
		 * problem here as mod_setenv might get called multiple times
		 *
		 * fastcgi-auth might lead to a COMEBACK too
		 * fastcgi again dead server too
		 */

		if (r->conf.log_request_handling) {
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "-- parsed Request-URI");
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "Request-URI     : %s", r->target.ptr);
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "URI-scheme      : %s", r->uri.scheme.ptr);
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "URI-authority   : %s", r->uri.authority.ptr);
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "URI-path (clean): %s", r->uri.path.ptr);
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "URI-query       : %.*s",
			  BUFFER_INTLEN_PTR(&r->uri.query));
		}


		rc = plugins_call_handle_uri_clean(r);
		if (HANDLER_GO_ON != rc) return rc;

		if (__builtin_expect( (r->http_method == HTTP_METHOD_OPTIONS), 0)
		    && r->uri.path.ptr[0] == '*' && r->uri.path.ptr[1] == '\0')
			return http_response_prepare_options_star(r);

		if (__builtin_expect( (r->http_method == HTTP_METHOD_CONNECT), 0)
		    && (r->handler_module || !r->h2_connect_ext))
			return http_response_prepare_connect(r);


		/*
		 * border between logical and physical
		 * logical path (URI) becomes a physical filename
		 */


		/* docroot: set r->physical.doc_root and might set r->server_name */
		buffer_clear(&r->physical.doc_root);

		rc = plugins_call_handle_docroot(r);
		if (HANDLER_GO_ON != rc) return rc;


		/* transform r->uri.path to r->physical.rel_path (relative file path) */
		buffer_copy_buffer(&r->physical.rel_path, &r->uri.path);
#if defined(__WIN32) || defined(__CYGWIN__)
		/* strip dots from the end and spaces
		 *
		 * windows/dos handle those filenames as the same file
		 *
		 * foo == foo. == foo..... == "foo...   " == "foo..  ./"
		 *
		 * This will affect in some cases PATHINFO
		 *
		 * on native windows we could prepend the filename with \\?\ to circumvent
		 * this behaviour. I have no idea how to push this through cygwin
		 *
		 * */
		{
			buffer *b = &r->physical.rel_path;
			size_t len = buffer_clen(b);

			/* strip trailing " /" or "./" once */
			if (len > 1 &&
			    b->ptr[len - 1] == '/' &&
			    (b->ptr[len - 2] == ' ' || b->ptr[len - 2] == '.')) {
				len -= 2;
			}
			/* strip all trailing " " and "." */
			while (len > 0 &&  ( ' ' == b->ptr[len-1] || '.' == b->ptr[len-1] ) ) --len;
			buffer_truncate(b, len);
		}
#endif
		/* MacOS X and Windows (typically) case-insensitive filesystems */
		if (r->conf.force_lowercase_filenames) {
			buffer_to_lower(&r->physical.rel_path);
		}


		/* compose physical filename: physical.path = doc_root + rel_path */
		if (buffer_is_unset(&r->physical.doc_root))
			buffer_copy_buffer(&r->physical.doc_root, r->conf.document_root);
		buffer_copy_buffer(&r->physical.basedir, &r->physical.doc_root);
		buffer_copy_path_len2(&r->physical.path,
		                      BUF_PTR_LEN(&r->physical.doc_root),
		                      BUF_PTR_LEN(&r->physical.rel_path));

			rc = plugins_call_handle_physical(r);
			if (HANDLER_GO_ON != rc) return rc;

			if (r->conf.log_request_handling) {
				log_error(r->conf.errh, __FILE__, __LINE__,
				  "-- logical -> physical");
				log_error(r->conf.errh, __FILE__, __LINE__,
				  "Doc-Root     : %s", r->physical.doc_root.ptr);
				log_error(r->conf.errh, __FILE__, __LINE__,
				  "Basedir      : %s", r->physical.basedir.ptr);
				log_error(r->conf.errh, __FILE__, __LINE__,
				  "Rel-Path     : %s", r->physical.rel_path.ptr);
				log_error(r->conf.errh, __FILE__, __LINE__,
				  "Path         : %s", r->physical.path.ptr);
			}
	}

	if (NULL != r->handler_module) return HANDLER_GO_ON;

	/*
	 * No module grabbed the request yet (like mod_access)
	 *
	 * Go on and check if the file exists at all
	 */

		rc = http_response_physical_path_check(r);
		if (HANDLER_GO_ON != rc) return rc;

		/* r->physical.path is non-empty and exists in the filesystem */

		if (r->conf.log_request_handling) {
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "-- handling subrequest");
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "Path         : %s", r->physical.path.ptr);
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "URI          : %s", r->uri.path.ptr);
			log_error(r->conf.errh, __FILE__, __LINE__,
			  "Pathinfo     : %s", r->pathinfo.ptr
			                     ? r->pathinfo.ptr
			                     : "");
		}

		/* call the handlers */
		rc = plugins_call_handle_subrequest_start(r);
		if (HANDLER_GO_ON != rc) return rc;

		if (__builtin_expect( (NULL == r->handler_module), 0)) {
			/* no handler; finish request */
			if (__builtin_expect( (0 == r->http_status), 0)) {
				if (r->http_method == HTTP_METHOD_OPTIONS) {
					http_response_body_clear(r, 0);
					http_response_prepare_options_star(r); /*(treat like "*")*/
				}
				else if (r->http_method == HTTP_METHOD_CONNECT)
					/* 405 Method Not Allowed */
					return http_status_set_error_close(r, 405);
					/*return http_response_prepare_connect(r);*/
				else if (!http_method_get_head_query_post(r->http_method))
					r->http_status = 501;
				else
					r->http_status = 403;
			}
			return HANDLER_FINISHED;
		}

		return HANDLER_GO_ON;
}


__attribute_cold__
__attribute_noinline__
static handler_t http_response_comeback (request_st * const r)
{
    if (NULL != r->handler_module || !buffer_is_unset(&r->physical.path))
        return HANDLER_GO_ON;

    request_config_reset(r);

    if (__builtin_expect( (r->http_host != NULL), 1))
        buffer_copy_string_len_lc(&r->uri.authority, BUF_PTR_LEN(r->http_host));
    else /*(buffer_blank(&r->uri.authority) w/o code inline)*/
        buffer_copy_string_len(&r->uri.authority, CONST_STR_LEN(""));

    int status = http_request_parse_target(r, r->con->proto_default_port);
    if (0 == status) {
        r->conditional_is_valid = (1 << COMP_SERVER_SOCKET)
                                | (1 << COMP_HTTP_SCHEME)
                                | (1 << COMP_HTTP_HOST)
                                | (1 << COMP_HTTP_REMOTE_IP)
                                | (1 << COMP_HTTP_REQUEST_METHOD)
                                | (1 << COMP_HTTP_URL)
                                | (1 << COMP_HTTP_QUERY_STRING)
                                | (1 << COMP_HTTP_REQUEST_HEADER);
        return HANDLER_GO_ON;
    }
    else {
        r->conditional_is_valid = (1 << COMP_SERVER_SOCKET)
                                | (1 << COMP_HTTP_REMOTE_IP);
        config_cond_cache_reset(r);
        return http_status_set_error_close(r, status);
    }
}


__attribute_cold__
static void
http_response_errdoc_init (request_st * const r)
{
    /* modules that produce headers required with error response should
     * typically also produce an error document.  Make an exception for
     * mod_auth WWW-Authenticate response header. */
    buffer *www_auth = NULL;
    if (401 == r->http_status) {
        const buffer * const vb =
          http_header_response_get(r, HTTP_HEADER_WWW_AUTHENTICATE,
                                   CONST_STR_LEN("WWW-Authenticate"));
        if (NULL != vb) buffer_copy_buffer((www_auth = buffer_init()), vb);
    }

    buffer_reset(&r->physical.path);
    r->resp_htags = 0;
    array_reset_data_strings(&r->resp_headers);
    http_response_body_clear(r, 0);

    if (NULL != www_auth) {
        http_header_response_set(r, HTTP_HEADER_WWW_AUTHENTICATE,
                                 CONST_STR_LEN("WWW-Authenticate"),
                                 BUF_PTR_LEN(www_auth));
        buffer_free(www_auth);
    }
}


__attribute_cold__
static void
http_response_static_errdoc (request_st * const r)
{
    if (NULL == r->handler_module
        ? r->error_handler_saved_status >= 65535
        : (!r->conf.error_intercept || r->error_handler_saved_status))
        return;

    http_response_errdoc_init(r);
    r->resp_body_finished = 1;

    /* try to send static errorfile */
    if (r->conf.errorfile_prefix) {
        buffer_copy_buffer(&r->physical.path, r->conf.errorfile_prefix);
        buffer_append_int(&r->physical.path, r->http_status);
        buffer_append_string_len(&r->physical.path, CONST_STR_LEN(".html"));
        stat_cache_entry *sce =
          stat_cache_get_entry_open(&r->physical.path, r->conf.follow_symlink);
        if (sce && 0 == http_chunk_append_file_ref(r, sce)) {
            const buffer *content_type = stat_cache_content_type_get(sce, r);
            if (content_type)
                http_header_response_set(r, HTTP_HEADER_CONTENT_TYPE,
                                         CONST_STR_LEN("Content-Type"),
                                         BUF_PTR_LEN(content_type));
            return;
        }
        buffer_clear(&r->physical.path);
    }

    /* build default error-page */
    buffer * const b = chunkqueue_append_buffer_open(&r->write_queue);
    buffer_copy_string_len(b, CONST_STR_LEN(
      "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
      "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\n"
      "         \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
      "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n"
      " <head>\n"
      "  <title>"));
    http_status_append(b, r->http_status);
    buffer_append_string_len(b, CONST_STR_LEN(
      "</title>\n"
      " </head>\n"
      " <body>\n"
      "  <h1>"));
    http_status_append(b, r->http_status);
    buffer_append_string_len(b, CONST_STR_LEN(
      "</h1>\n"
      " </body>\n"
      "</html>\n"));
    chunkqueue_append_buffer_commit(&r->write_queue);

    http_header_response_set(r, HTTP_HEADER_CONTENT_TYPE,
                             CONST_STR_LEN("Content-Type"),
                             CONST_STR_LEN("text/html"));
}


__attribute_cold__
static void
http_response_merge_trailers (request_st * const r)
{
    /* attempt to merge trailers into headers; header not yet sent by caller */
    if (buffer_is_blank(&r->gw_dechunk->b)) return;
    const int done = r->gw_dechunk->done;
    if (!done) return; /* XXX: !done; could scan for '\n' and send only those */

    /* do not include trailers if success status (when response was read from
     * backend) subsequently changed to error status.  http_chunk could add the
     * trailers, but such actions are better on a different code layer than in
     * http_chunk.c */
    if (done < 400 && r->http_status >= 400) return;

    /* XXX: trailers passed through; no sanity check currently done
     * https://tools.ietf.org/html/rfc7230#section-4.1.2
     *
     * Not checking for disallowed fields
     * Not handling (deprecated) line wrapping
     * Not strictly checking fields
     */
    const char *k = strchr(r->gw_dechunk->b.ptr, '\n'); /*(skip final chunk)*/
    if (NULL == k) return; /*(should not happen)*/
    ++k;
    for (const char *v, *e; (e = strchr(k, '\n')); k = e+1) {
        v = memchr(k, ':', (size_t)(e - k));
        if (NULL == v || v == k || *k == ' ' || *k == '\t') continue;
        uint32_t klen = (uint32_t)(v - k);
        do { ++v; } while (*v == ' ' || *v == '\t');
        if (*v == '\r' || *v == '\n') continue;
        enum http_header_e id = http_header_hkey_get(k, klen);
        http_header_response_insert(r, id, k, klen, v, (size_t)(e - v));
    }
    http_header_response_unset(r, HTTP_HEADER_OTHER, CONST_STR_LEN("Trailer"));
    buffer_clear(&r->gw_dechunk->b);
}


__attribute_noinline__
static handler_t
http_response_write_prepare(request_st * const r)
{
    switch (r->http_status) {
      case 200: /* common case */
        break;
      case 204: /* class: header only */
      case 205:
      case 304:
        /* disable chunked encoding again as we have no body */
        http_response_body_clear(r, 1);
        /* no Content-Body, no Content-Length */
        http_header_response_unset(r, HTTP_HEADER_CONTENT_LENGTH,
                                   CONST_STR_LEN("Content-Length"));
        r->resp_body_finished = 1;
        break;
      default: /* class: header + body */
        /* only custom body for 4xx and 5xx */
        if (r->http_status >= 400 && r->http_status < 600)
            http_response_static_errdoc(r);
        break;
    }

    if (r->gw_dechunk)
        http_response_merge_trailers(r);

    /* Allow filter plugins to change response headers */
    switch (plugins_call_handle_response_start(r)) {
      case HANDLER_GO_ON:
      case HANDLER_FINISHED:
        break;
      default:
        log_error(r->conf.errh, __FILE__, __LINE__,
          "response_start plugin failed");
        return HANDLER_ERROR;
    }

    if (r->resp_body_finished) {
        /* check for Range request (current impl requires resp_body_finished) */
        if (r->conf.range_requests && r->http_status == 200
            && http_range_rfc7233(r) >= 400)
            http_response_static_errdoc(r); /* 416 Range Not Satisfiable */

        /* set content-length if length is known and not already set */
        if (!(r->resp_htags
              & (light_bshift(HTTP_HEADER_CONTENT_LENGTH)
                |light_bshift(HTTP_HEADER_TRANSFER_ENCODING)))) {
            off_t qlen = chunkqueue_length(&r->write_queue);
            /**
             * The Content-Length header can only be sent if we have content:
             * - HEAD does not have a content-body (but can have content-length)
             * - 1xx, 204 and 304 does not have a content-body
             *   (RFC 2616 Section 4.3)
             *
             * Otherwise generate a Content-Length header
             * (if chunked encoding is not available)
             *
             * (should not reach here if 1xx (r->http_status < 200))
             */
            if (qlen > 0) {
                buffer_append_int(
                  http_header_response_set_ptr(r, HTTP_HEADER_CONTENT_LENGTH,
                                               CONST_STR_LEN("Content-Length")),
                  qlen);
            }
            else if (r->http_method != HTTP_METHOD_HEAD
                     && r->http_status != 204 && r->http_status != 304) {
                /* Content-Length: 0 is important for Redirects (301, ...) as
                 * there might be content. */
                http_header_response_set(r, HTTP_HEADER_CONTENT_LENGTH,
                                         CONST_STR_LEN("Content-Length"),
                                         CONST_STR_LEN("0"));
            }
        }
    }
    else if (r->http_version == HTTP_VERSION_2) {
        /* handled by HTTP/2 framing */
    }
    else {
        /**
         * response is not yet finished, but we have all headers
         *
         * keep-alive requires one of:
         * - Content-Length: ... (HTTP/1.0 and HTTP/1.0)
         * - Transfer-Encoding: chunked (HTTP/1.1)
         * - Upgrade: ... (lighttpd then acts as transparent proxy)
         */

        if (!(r->resp_htags
              & (light_bshift(HTTP_HEADER_CONTENT_LENGTH)
                |light_bshift(HTTP_HEADER_TRANSFER_ENCODING)
                |light_bshift(HTTP_HEADER_UPGRADE)))) {
            if (r->http_method == HTTP_METHOD_CONNECT && r->http_status == 200){
                /*(no transfer-encoding if successful CONNECT)*/
            }
            else if (r->http_version == HTTP_VERSION_1_1) {
                off_t qlen = chunkqueue_length(&r->write_queue);
                r->resp_send_chunked = 1;
                if (r->resp_decode_chunked) {
                    /*(reconstitute initial partially-decoded chunk)*/
                    off_t gw_chunked = r->gw_dechunk->gw_chunked;
                    if (gw_chunked >= 2)
                        qlen += gw_chunked - 2;
                    else if (1 == gw_chunked)
                        chunkqueue_append_mem(&r->write_queue,
                                              CONST_STR_LEN("\r"));
                    else {
                        if (qlen)
                            chunkqueue_append_mem(&r->write_queue,
                                                  CONST_STR_LEN("\r\n"));
                        const buffer * const hdr = &r->gw_dechunk->b;
                        if (!buffer_is_blank(hdr)) /*(partial chunked header)*/
                            chunkqueue_append_mem(&r->write_queue,
                                                  BUF_PTR_LEN(hdr));
                    }
                }
                else if (qlen) {
                        chunkqueue_append_mem(&r->write_queue,
                                              CONST_STR_LEN("\r\n"));
                }
                if (qlen) {
                    /* create initial Transfer-Encoding: chunked segment */
                    buffer * const b =
                      chunkqueue_prepend_buffer_open(&r->write_queue);
                    buffer_append_uint_hex(b, (uintmax_t)qlen);
                    buffer_append_string_len(b, CONST_STR_LEN("\r\n"));
                    chunkqueue_prepend_buffer_commit(&r->write_queue);
                }
                http_header_response_append(r, HTTP_HEADER_TRANSFER_ENCODING,
                                            CONST_STR_LEN("Transfer-Encoding"),
                                            CONST_STR_LEN("chunked"));
            }
            else { /* if (r->http_version == HTTP_VERSION_1_0) */
                r->keep_alive = 0;
            }
        }
    }

    if (r->http_method == HTTP_METHOD_HEAD) {
        /* HEAD request is like a GET, but without the content */
        http_response_body_clear(r, 1);
        r->resp_body_finished = 1;
    }

    return HANDLER_GO_ON;
}


__attribute_cold__
static int
http_response_call_error_handler (request_st * const r, const buffer * const error_handler)
{
    /* call error-handler */

    /* set REDIRECT_STATUS to save current HTTP status code
     * for access by dynamic handlers
     * https://redmine.lighttpd.net/issues/1828 */
    buffer_append_int(
      http_header_env_set_ptr(r, CONST_STR_LEN("REDIRECT_STATUS")),
      r->http_status);

    if (error_handler == r->conf.error_handler) {
        plugins_call_handle_request_reset(r);

        if (r->reqbody_length) {
            if (r->reqbody_length != r->reqbody_queue.bytes_in)
                r->keep_alive = 0;
            r->reqbody_length = 0;
            chunkqueue_reset(&r->reqbody_queue);
        }

        r->con->is_writable = 1;
        r->error_handler_saved_status = r->http_status;
        r->error_handler_saved_method = r->http_method;
        r->http_method = HTTP_METHOD_GET;
    }
    else { /*(preserve behavior for server.error-handler-404)*/
        /*(negative to flag old behavior)*/
        r->error_handler_saved_status = -r->http_status;
    }

    if (r->http_version == HTTP_VERSION_UNSET)
        r->http_version = HTTP_VERSION_1_0;

    buffer_copy_buffer(&r->target, error_handler);
    http_response_errdoc_init(r);
    r->http_status = 0; /*(after http_response_errdoc_init())*/
    return 1;
}


__attribute_cold__
__attribute_noinline__
static int
http_response_has_error_handler (request_st * const r)
{
    if (r->error_handler_saved_status > 0)
        r->http_method = r->error_handler_saved_method;
    if (NULL == r->handler_module || r->conf.error_intercept) {
        if (__builtin_expect( (r->error_handler_saved_status), 0)) {
            const int subreq_status = r->http_status;
            if (r->error_handler_saved_status > 0)
                r->http_status = r->error_handler_saved_status;
            else if (r->http_status == 404 || r->http_status == 403)
                /* error-handler-404 is a 404 */
                r->http_status = -r->error_handler_saved_status;
            else {
                /* error-handler-404 is back and has generated content */
                /* if Status: was set, take it otherwise use 200 */
            }
            if (200 <= subreq_status && subreq_status <= 299) {
                /*(flag value to indicate that error handler succeeded)
                 *(for (NULL == r->handler_module))*/
                r->error_handler_saved_status = 65535; /* >= 1000 */
            }
        }
        else if (__builtin_expect( (r->http_status >= 400), 0)) {
            const buffer *error_handler = NULL;
            if (r->conf.error_handler)
                error_handler = r->conf.error_handler;
            else if ((r->http_status == 404 || r->http_status == 403)
                   && r->conf.error_handler_404)
                error_handler = r->conf.error_handler_404;

            if (error_handler)
                return http_response_call_error_handler(r, error_handler);
        }
    }
    return 0;
}


handler_t
http_response_handler (request_st * const r)
{
  int rc;
  do {
    const plugin *p = r->handler_module;
    if (NULL != p
        || ((rc = http_response_prepare(r)) == HANDLER_GO_ON
            && NULL != (p = r->handler_module)))
        rc = p->handle_subrequest(r, p->data);

    switch (rc) {
      case HANDLER_WAIT_FOR_EVENT:
        if (!r->resp_body_finished
            && (!r->resp_body_started
                || 0 == (r->conf.stream_response_body
                         & (FDEVENT_STREAM_RESPONSE
                           |FDEVENT_STREAM_RESPONSE_BUFMIN))))
            return HANDLER_WAIT_FOR_EVENT; /* come back here */
        /* response headers received from backend; start response */
        __attribute_fallthrough__
      case HANDLER_GO_ON:
      case HANDLER_FINISHED:
        if (r->http_status == 0) r->http_status = 200;
        if ((__builtin_expect( (r->http_status < 400), 1)
             && __builtin_expect( (0 == r->error_handler_saved_status), 1))
            || __builtin_expect( (!http_response_has_error_handler(r)), 1))
            /* we have something to send; go on */
            /*(CON_STATE_RESPONSE_START; transient state)*/
            return http_response_write_prepare(r);
        __attribute_fallthrough__
      case HANDLER_COMEBACK:
        http_response_comeback(r);
        rc = HANDLER_COMEBACK;
        continue;
      /*case HANDLER_ERROR:*/
      default:
        return HANDLER_ERROR; /* something went wrong */
    }
  } while (rc == HANDLER_COMEBACK);
 #ifndef __COVERITY__
  return HANDLER_ERROR; /* should not happen */ /*(not reached)*/
 #endif
}
