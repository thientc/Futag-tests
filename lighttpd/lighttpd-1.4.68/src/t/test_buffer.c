#include "first.h"

#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.c"

static void run_buffer_path_simplify(buffer *psrc, buffer *pdest, const char *in, size_t in_len, const char *out, size_t out_len) {
	buffer_copy_string_len(psrc, in, in_len);
	pdest = psrc; /*(buffer_path_simplify() now takes only one arg)*/

	buffer_path_simplify(pdest);

	if (!buffer_eq_slen(pdest, out, out_len)) {
		fprintf(stderr,
			"%s.%d: buffer_path_simplify('%s') failed: expected '%s', got '%s'\n",
			__FILE__,
			__LINE__,
			in,
			out,
			pdest->ptr);
		fflush(stderr);
		abort();
	} else {
		buffer_path_simplify(pdest);

		if (!buffer_eq_slen(pdest, out, out_len)) {
			fprintf(stderr,
				"%s.%d: buffer_path_simplify('%s') failed - not idempotent: expected '%s', got '%s'\n",
				__FILE__,
				__LINE__,
				in,
				out,
				pdest->ptr);
			fflush(stderr);
			abort();
		}
	}
}

static void test_buffer_path_simplify_with(buffer *psrc, buffer *pdest) {
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN(""), CONST_STR_LEN(""));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/"), CONST_STR_LEN("/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("//"), CONST_STR_LEN("/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc"), CONST_STR_LEN("abc"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc//"), CONST_STR_LEN("abc/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc/./xyz"), CONST_STR_LEN("abc/xyz"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc/.//xyz"), CONST_STR_LEN("abc/xyz"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc/../xyz"), CONST_STR_LEN("/xyz"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/abc/./xyz"), CONST_STR_LEN("/abc/xyz"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/abc//./xyz"), CONST_STR_LEN("/abc/xyz"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/abc/../xyz"), CONST_STR_LEN("/xyz"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc/../xyz/."), CONST_STR_LEN("/xyz/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/abc/../xyz/."), CONST_STR_LEN("/xyz/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("abc/./xyz/.."), CONST_STR_LEN("abc/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/abc/./xyz/.."), CONST_STR_LEN("/abc/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("."), CONST_STR_LEN(""));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN(".."), CONST_STR_LEN(""));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("..."), CONST_STR_LEN("..."));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("...."), CONST_STR_LEN("...."));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN(".../"), CONST_STR_LEN(".../"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("./xyz/.."), CONST_STR_LEN("/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN(".//xyz/.."), CONST_STR_LEN("/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/./xyz/.."), CONST_STR_LEN("/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN(".././xyz/.."), CONST_STR_LEN("/"));
	run_buffer_path_simplify(psrc, pdest, CONST_STR_LEN("/.././xyz/.."), CONST_STR_LEN("/"));
}

static void test_buffer_path_simplify(void) {
	buffer *psrc = buffer_init();

	/* test with using the same buffer and with using different buffers */
	test_buffer_path_simplify_with(psrc, psrc);

	buffer_free(psrc);
}

static void test_buffer_to_lower_upper(void) {
	buffer *psrc = buffer_init();

	buffer_copy_string_len(psrc, CONST_STR_LEN("0123456789abcdefghijklmnopqrstuvwxyz"));
	buffer_to_lower(psrc);
	assert(buffer_eq_slen(psrc, CONST_STR_LEN("0123456789abcdefghijklmnopqrstuvwxyz")));
	buffer_to_upper(psrc);
	assert(buffer_eq_slen(psrc, CONST_STR_LEN("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
	buffer_to_upper(psrc);
	assert(buffer_eq_slen(psrc, CONST_STR_LEN("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
	buffer_to_lower(psrc);
	assert(buffer_eq_slen(psrc, CONST_STR_LEN("0123456789abcdefghijklmnopqrstuvwxyz")));

	buffer_free(psrc);
}

static void test_buffer_string_space(void) {
	buffer *b = buffer_init();
	size_t space;

	space = buffer_string_space(b);
	assert(0 == space);
	buffer_copy_string_len(b, CONST_STR_LEN(""));
	space = buffer_string_space(b);
	assert(space > 0);
	assert(space + buffer_string_length(b) == b->size - 1);
	buffer_commit(b, b->size - 1);
	assert(b->used == b->size);
	space = buffer_string_space(b);
	assert(0 == space);

	buffer_free(b);
}

static void test_buffer_append_path_len(void) {
	buffer *b = buffer_init();

	buffer_append_path_len(b, CONST_STR_LEN("a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("/a")));
	buffer_clear(b);
	buffer_append_path_len(b, CONST_STR_LEN("a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("/a")));
	buffer_clear(b);
	buffer_append_path_len(b, CONST_STR_LEN("/a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("/a")));
	buffer_copy_string_len(b, CONST_STR_LEN("/"));
	buffer_append_path_len(b, CONST_STR_LEN("a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("/a")));
	buffer_copy_string_len(b, CONST_STR_LEN("/"));
	buffer_append_path_len(b, CONST_STR_LEN("/a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("/a")));
	buffer_copy_string_len(b, CONST_STR_LEN("a"));
	buffer_append_path_len(b, CONST_STR_LEN("a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("a/a")));
	buffer_copy_string_len(b, CONST_STR_LEN("a/"));
	buffer_append_path_len(b, CONST_STR_LEN("a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("a/a")));
	buffer_copy_string_len(b, CONST_STR_LEN("a/"));
	buffer_append_path_len(b, CONST_STR_LEN("/a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("a/a")));
	buffer_copy_string_len(b, CONST_STR_LEN("/a/"));
	buffer_append_path_len(b, CONST_STR_LEN("/a"));
	assert(buffer_eq_slen(b, CONST_STR_LEN("/a/a")));

	buffer_free(b);
}

static void test_buffer_append_bs_escaped(void) {
    buffer *b = buffer_init();

    buffer_append_bs_escaped_json(b, CONST_STR_LEN(" "));
    assert(buffer_eq_slen(b, CONST_STR_LEN(" ")));
    buffer_clear(b);
    buffer_append_bs_escaped_json(b, CONST_STR_LEN("\0"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("\\u0000")));
    buffer_clear(b);
    buffer_append_bs_escaped_json(b, CONST_STR_LEN("\1"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("\\u0001")));
    buffer_clear(b);
    buffer_append_bs_escaped_json(b, CONST_STR_LEN("\n"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("\\n")));
    buffer_clear(b);
    buffer_append_bs_escaped_json(b, CONST_STR_LEN("é"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("é")));
    buffer_clear(b);
    buffer_append_bs_escaped_json(b, CONST_STR_LEN("ö"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("ö")));

  #if 0
    buffer_clear(b);
    magnet_buffer_append_bsdec(b, CONST_STR_LEN("\\u00E9"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("é")));
    buffer_clear(b);
    magnet_buffer_append_bsdec(b, CONST_STR_LEN("\\u00F6"));
    assert(buffer_eq_slen(b, CONST_STR_LEN("ö")));
  #endif

    /* TODO: more */

    buffer_free(b);
}

void test_buffer (void);
void test_buffer (void)
{
	test_buffer_path_simplify();
	test_buffer_to_lower_upper();
	test_buffer_string_space();
	test_buffer_append_path_len();
	test_buffer_append_bs_escaped();
}
