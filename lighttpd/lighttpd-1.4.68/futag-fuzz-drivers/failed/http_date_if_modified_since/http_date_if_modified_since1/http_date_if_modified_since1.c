#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "http_date.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(uint32_t)+sizeof(unix_time64_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(uint32_t)+sizeof(unix_time64_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_CSTRING
    char * rstr_ifmod = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_ifmod, 0, dyn_size[0] + 1);
    memcpy(rstr_ifmod, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_ifmod = rstr_ifmod;
    
    //GEN_BUILTIN
    uint32_t b__ifmodlen;
    memcpy(&b__ifmodlen, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_QUALIFIED
    const uint32_t q_b__ifmodlen = b__ifmodlen;
    
    //GEN_BUILTIN
    unix_time64_t b__lmtime;
    memcpy(&b__lmtime, pos, sizeof(unix_time64_t));
    pos += sizeof(unix_time64_t);
    //GEN_QUALIFIED
    const unix_time64_t q_b__lmtime = b__lmtime;
    
    //FUNCTION_CALL
    http_date_if_modified_since(str_ifmod ,q_b__ifmodlen ,q_b__lmtime );
    //FREE
    if (rstr_ifmod) {
        free(rstr_ifmod);
        rstr_ifmod = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-http_date.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_date.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_date.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_date_if_modified_since/http_date_if_modified_since1/http_date_if_modified_since1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_date_if_modified_since/http_date_if_modified_since1/http_date_if_modified_since1.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_date_if_modified_since/http_date_if_modified_since1/http_date_if_modified_since1.c:7:
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_date.h:11:
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sys-time.h:37:1: error: static declaration of 'timegm' follows non-static declaration
timegm (const struct tm * const tm);
^
/usr/include/time.h:249:15: note: previous declaration is here
extern time_t timegm (struct tm *__tp) __THROW;
              ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
