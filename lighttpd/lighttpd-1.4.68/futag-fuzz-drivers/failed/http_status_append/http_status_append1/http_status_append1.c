#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "http_kv.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_VAR_FUNCTION
    buffer * s__b = chunk_buffer_acquire();
    //GEN_BUILTIN
    int b__status;
    memcpy(&b__status, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__status = b__status;
    
    //FUNCTION_CALL
    http_status_append(s__b ,q_b__status );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-http_kv.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_kv.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_kv.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_status_append/http_status_append1/http_status_append1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_status_append/http_status_append1/http_status_append1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_status_append/http_status_append1/http_status_append1.c:15:21: warning: implicit declaration of function 'chunk_buffer_acquire' is invalid in C99 [-Wimplicit-function-declaration]
    buffer * s__b = chunk_buffer_acquire();
                    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_status_append/http_status_append1/http_status_append1.c:15:14: warning: incompatible integer to pointer conversion initializing 'buffer *' with an expression of type 'int' [-Wint-conversion]
    buffer * s__b = chunk_buffer_acquire();
             ^      ~~~~~~~~~~~~~~~~~~~~~~
2 warnings generated.
/usr/bin/ld: /tmp/http_status_append1-76f814.o: in function `LLVMFuzzerTestOneInput':
http_status_append1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x16c): undefined reference to `chunk_buffer_acquire'
/usr/bin/ld: http_status_append1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1f8): undefined reference to `http_status_append'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
