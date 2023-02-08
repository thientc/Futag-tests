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
    if (Fuzz_Size < 1 + 0 + sizeof(rsize_t)+sizeof(errno_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(rsize_t)+sizeof(errno_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_CSTRING
    char * str_s = (char *) malloc(dyn_size[0] + 1);
    memset(str_s, 0, dyn_size[0] + 1);
    memcpy(str_s, pos, dyn_size[0] );
    pos += dyn_size[0];
    
    //GEN_BUILTIN
    rsize_t b__maxsize;
    memcpy(&b__maxsize, pos, sizeof(rsize_t));
    pos += sizeof(rsize_t);
    //GEN_QUALIFIED
    const rsize_t q_b__maxsize = b__maxsize;
    
    //GEN_BUILTIN
    errno_t b__errnum;
    memcpy(&b__errnum, pos, sizeof(errno_t));
    pos += sizeof(errno_t);
    //GEN_QUALIFIED
    const errno_t q_b__errnum = b__errnum;
    
    //FUNCTION_CALL
    ck_strerror_s(str_s ,q_b__maxsize ,q_b__errnum );
    //FREE
    if (str_s) {
        free(str_s);
        str_s = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_strerror_s/ck_strerror_s1/ck_strerror_s1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_strerror_s/ck_strerror_s1/ck_strerror_s1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/ck_strerror_s1-cf7fa6.o: in function `LLVMFuzzerTestOneInput':
ck_strerror_s1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x3c5): undefined reference to `ck_strerror_s'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
