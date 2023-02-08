#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "fdlog.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1)));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_CSTRING
    char * rstr_1_fn = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_1_fn, 0, dyn_size[0] + 1);
    memcpy(rstr_1_fn, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_1_fn = rstr_1_fn;
    //GEN_VAR_FUNCTION
    fdlog_st * s__fdlog = fdlog_open(str_1_fn);
    //FUNCTION_CALL
    fdlog_free(s__fdlog );
    //FREE
    if (rstr_1_fn) {
        free(rstr_1_fn);
        rstr_1_fn = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o fdlog.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/fdlog.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/fdlog.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_free/fdlog_free2/fdlog_free2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_free/fdlog_free2/fdlog_free2.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/fdlog_free2-c8c367.o: in function `LLVMFuzzerTestOneInput':
fdlog_free2.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x2ae): undefined reference to `fdlog_open'
/usr/bin/ld: fdlog_free2.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x2c1): undefined reference to `fdlog_free'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
