#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "array.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(uint32_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    uint32_t b_1_n;
    memcpy(&b_1_n, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_VAR_FUNCTION
    array * s__a = array_init(b_1_n);
    
    //GEN_VAR_FUNCTION
    buffer * s__b = chunk_buffer_acquire();
    //FUNCTION_CALL
    array_match_value_suffix(s__a ,s__b );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o array.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/array.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/array.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_match_value_suffix/array_match_value_suffix1/array_match_value_suffix1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_match_value_suffix/array_match_value_suffix1/array_match_value_suffix1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/array_match_value_suffix/array_match_value_suffix1/array_match_value_suffix1.c:22:21: warning: implicit declaration of function 'chunk_buffer_acquire' is invalid in C99 [-Wimplicit-function-declaration]
    buffer * s__b = chunk_buffer_acquire();
                    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/array_match_value_suffix/array_match_value_suffix1/array_match_value_suffix1.c:22:14: warning: incompatible integer to pointer conversion initializing 'buffer *' with an expression of type 'int' [-Wint-conversion]
    buffer * s__b = chunk_buffer_acquire();
             ^      ~~~~~~~~~~~~~~~~~~~~~~
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/array_match_value_suffix/array_match_value_suffix1/array_match_value_suffix1.c:24:5: warning: ignoring return value of function declared with pure attribute [-Wunused-value]
    array_match_value_suffix(s__a ,s__b );
    ^~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~
3 warnings generated.
/usr/bin/ld: /tmp/array_match_value_suffix1-640d49.o: in function `LLVMFuzzerTestOneInput':
array_match_value_suffix1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1d9): undefined reference to `array_init'
/usr/bin/ld: array_match_value_suffix1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1e7): undefined reference to `chunk_buffer_acquire'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
