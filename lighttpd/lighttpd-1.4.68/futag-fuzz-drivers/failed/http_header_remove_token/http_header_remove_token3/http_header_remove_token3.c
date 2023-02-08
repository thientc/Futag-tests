#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "sys-strings.h"
#include "http_header.h"
#include "array.h"
#include "request.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(uint32_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(uint32_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_CSTRING
    char * rstr_m = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_m, 0, dyn_size[0] + 1);
    memcpy(rstr_m, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_m = rstr_m;
    
    //GEN_BUILTIN
    uint32_t b__mlen;
    memcpy(&b__mlen, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_QUALIFIED
    const uint32_t q_b__mlen = b__mlen;
    
    //FUNCTION_CALL
    http_header_remove_token(s__b ,str_m ,q_b__mlen );
    //FREE
    if (rstr_m) {
        free(rstr_m);
        rstr_m = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-http_header.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_header.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_header.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_header_remove_token/http_header_remove_token3/http_header_remove_token3.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_header_remove_token/http_header_remove_token3/http_header_remove_token3.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_header_remove_token/http_header_remove_token3/http_header_remove_token3.c:11:
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/request.h:5:
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sys-time.h:37:1: error: static declaration of 'timegm' follows non-static declaration
timegm (const struct tm * const tm);
^
/usr/include/time.h:249:15: note: previous declaration is here
extern time_t timegm (struct tm *__tp) __THROW;
              ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
