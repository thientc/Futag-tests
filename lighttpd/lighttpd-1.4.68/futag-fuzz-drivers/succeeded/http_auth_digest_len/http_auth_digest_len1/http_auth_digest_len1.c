#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "mod_auth_api.h"
#include "http_header.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(int)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    int b_algo;
    memcpy(&b_algo, pos, sizeof(int));
    pos += sizeof(int);
    
    //FUNCTION_CALL
    http_auth_digest_len(b_algo );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o .libs/mod_auth_api.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/mod_auth_api.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/mod_auth_api.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/succeeded/http_auth_digest_len/http_auth_digest_len1/http_auth_digest_len1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/succeeded/http_auth_digest_len/http_auth_digest_len1/http_auth_digest_len1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_auth_digest_len/http_auth_digest_len1/http_auth_digest_len1.c:20:5: warning: ignoring return value of function declared with const attribute [-Wunused-value]
    http_auth_digest_len(b_algo );
    ^~~~~~~~~~~~~~~~~~~~ ~~~~~~
1 warning generated.

 */
