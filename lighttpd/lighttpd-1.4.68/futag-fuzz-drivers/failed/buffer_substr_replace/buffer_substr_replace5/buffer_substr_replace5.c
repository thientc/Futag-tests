#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned int)+sizeof(size_t)+sizeof(size_t)+sizeof(unsigned int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__b = http_method_buf(e_1_i);
    //GEN_BUILTIN
    size_t b__offset;
    memcpy(&b__offset, pos, sizeof(size_t));
    pos += sizeof(size_t);
    //GEN_QUALIFIED
    const size_t q_b__offset = b__offset;
    
    //GEN_BUILTIN
    size_t b__len;
    memcpy(&b__len, pos, sizeof(size_t));
    pos += sizeof(size_t);
    //GEN_QUALIFIED
    const size_t q_b__len = b__len;
    
    
    //GEN_ENUM
    unsigned int e_2_i_enum_index; 
    memcpy(&e_2_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_2_i = e_2_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__replace = http_method_buf(e_2_i);
    //FUNCTION_CALL
    buffer_substr_replace(s__b ,q_b__offset ,q_b__len ,s__replace );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-buffer.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/buffer.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/buffer.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_substr_replace/buffer_substr_replace5/buffer_substr_replace5.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_substr_replace/buffer_substr_replace5/buffer_substr_replace5.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_substr_replace/buffer_substr_replace5/buffer_substr_replace5.c:17:5: error: use of undeclared identifier 'http_method_t'
    http_method_t e_1_i = e_1_i_enum_index % 41;
    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_substr_replace/buffer_substr_replace5/buffer_substr_replace5.c:19:27: warning: implicit declaration of function 'http_method_buf' is invalid in C99 [-Wimplicit-function-declaration]
    const buffer * s__b = http_method_buf(e_1_i);
                          ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
1 warning and 2 errors generated.

 */
