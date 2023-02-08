#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "fdlog.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "fdevent.h"
#include "log.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(int)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(int))));
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
    //GEN_SIZE
    const int sz__1_fd = (const int) dyn_size[0];
    //GEN_BUILTIN
    int b__1_mode;
    memcpy(&b__1_mode, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__1_mode = b__1_mode;
    //GEN_VAR_FUNCTION
    fdlog_st * s__errh = fdlog_init(str_1_fn,sz__1_fd,q_b__1_mode);
    //FUNCTION_CALL
    fdlog_closeall(s__errh );
    //FREE
    if (rstr_1_fn) {
        free(rstr_1_fn);
        rstr_1_fn = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-fdlog_maint.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/fdlog_maint.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/fdlog_maint.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_closeall/fdlog_closeall1/fdlog_closeall1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_closeall/fdlog_closeall1/fdlog_closeall1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/fdlog_closeall1-761ed0.o: in function `LLVMFuzzerTestOneInput':
fdlog_closeall1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x38c): undefined reference to `fdlog_init'
/usr/bin/ld: fdlog_closeall1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x39f): undefined reference to `fdlog_closeall'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
