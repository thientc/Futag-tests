#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "http_etag.h"
#include <sys/stat.h>
#include "algo_md.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1)));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_CSTRING
    char * rstr_s = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_s, 0, dyn_size[0] + 1);
    memcpy(rstr_s, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char * str_s = rstr_s;
    
    //GEN_SIZE
    const int sz__weak_ok = (const int) dyn_size[0];
    
    //FUNCTION_CALL
    http_etag_matches(s__etag ,str_s ,sz__weak_ok );
    //FREE
    if (rstr_s) {
        free(rstr_s);
        rstr_s = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-http_etag.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_etag.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_etag.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_etag_matches/http_etag_matches3/http_etag_matches3.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_etag_matches/http_etag_matches3/http_etag_matches3.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_etag_matches/http_etag_matches3/http_etag_matches3.c:32:23: error: use of undeclared identifier 's__etag'
    http_etag_matches(s__etag ,str_s ,sz__weak_ok );
                      ^
1 error generated.

 */
