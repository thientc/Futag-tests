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
    if (Fuzz_Size < 3 + 0) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 3)));
    //generate random array of dynamic string sizes
    size_t dyn_size[3];
    srand(time(NULL));
    if(dyn_buffer == 0) dyn_size[0] = dyn_buffer; 
    else dyn_size[0] = rand() % dyn_buffer; 
    size_t remain = dyn_size[0];
    for(size_t i = 1; i< 3 - 1; i++){
        if(dyn_buffer - remain == 0) dyn_size[i] = dyn_buffer - remain;
        else dyn_size[i] = rand() % (dyn_buffer - remain);
        remain += dyn_size[i];
    }
    dyn_size[3 - 1] = dyn_buffer - remain;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_VAR_FUNCTION
    http_auth_require_t * s__require = http_auth_require_init();
    //GEN_CSTRING
    char * rstr_user = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_user, 0, dyn_size[0] + 1);
    memcpy(rstr_user, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_user = rstr_user;
    
    //GEN_CSTRING
    char * rstr_group = (char *) malloc(dyn_size[1] + 1);
    memset(rstr_group, 0, dyn_size[1] + 1);
    memcpy(rstr_group, pos, dyn_size[1] );
    pos += dyn_size[1];
    const char *const str_group = rstr_group;
    
    //GEN_CSTRING
    char * rstr_host = (char *) malloc(dyn_size[2] + 1);
    memset(rstr_host, 0, dyn_size[2] + 1);
    memcpy(rstr_host, pos, dyn_size[2] );
    pos += dyn_size[2];
    const char *const str_host = rstr_host;
    
    //FUNCTION_CALL
    http_auth_match_rules(s__require ,str_user ,str_group ,str_host );
    //FREE
    if (rstr_user) {
        free(rstr_user);
        rstr_user = NULL;
    }
    if (rstr_group) {
        free(rstr_group);
        rstr_group = NULL;
    }
    if (rstr_host) {
        free(rstr_host);
        rstr_host = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_auth_match_rules/http_auth_match_rules1/http_auth_match_rules1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_auth_match_rules/http_auth_match_rules1/http_auth_match_rules1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_auth_match_rules/http_auth_match_rules1/http_auth_match_rules1.c:53:5: warning: ignoring return value of function declared with pure attribute [-Wunused-value]
    http_auth_match_rules(s__require ,str_user ,str_group ,str_host );
    ^~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning generated.
/usr/bin/ld: /tmp/http_auth_match_rules1-97688b.o: in function `LLVMFuzzerTestOneInput':
http_auth_match_rules1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x509): undefined reference to `http_auth_require_init'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
