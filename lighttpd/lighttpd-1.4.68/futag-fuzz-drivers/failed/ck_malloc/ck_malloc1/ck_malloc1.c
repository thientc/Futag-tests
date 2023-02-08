#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "ck.h"
#include <errno.h>

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(size_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    size_t b_nbytes;
    memcpy(&b_nbytes, pos, sizeof(size_t));
    pos += sizeof(size_t);
    
    //FUNCTION_CALL
    ck_malloc(b_nbytes );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o ck.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ck.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ck.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_malloc/ck_malloc1/ck_malloc1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_malloc/ck_malloc1/ck_malloc1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/ck_malloc1-c334e9.o: in function `LLVMFuzzerTestOneInput':
ck_malloc1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1a7): undefined reference to `ck_malloc'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
