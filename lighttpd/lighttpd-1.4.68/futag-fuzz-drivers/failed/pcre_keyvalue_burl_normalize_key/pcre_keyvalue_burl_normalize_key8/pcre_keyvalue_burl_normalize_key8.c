#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "keyvalue.h"
#include "burl.h"
#include "log.h"
#include <pcre2.h>

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__t = http_method_buf(e_1_i);
    //FUNCTION_CALL
    pcre_keyvalue_burl_normalize_key(s__k ,s__t );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-keyvalue.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/keyvalue.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/keyvalue.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/pcre_keyvalue_burl_normalize_key/pcre_keyvalue_burl_normalize_key8/pcre_keyvalue_burl_normalize_key8.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/pcre_keyvalue_burl_normalize_key/pcre_keyvalue_burl_normalize_key8/pcre_keyvalue_burl_normalize_key8.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/pcre_keyvalue_burl_normalize_key/pcre_keyvalue_burl_normalize_key8/pcre_keyvalue_burl_normalize_key8.c:11:
/usr/include/pcre2.h:971:2: error: PCRE2_CODE_UNIT_WIDTH must be defined before including pcre2.h.
#error PCRE2_CODE_UNIT_WIDTH must be defined before including pcre2.h.
 ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
