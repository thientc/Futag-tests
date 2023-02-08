#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "array.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__b = http_method_buf(e_1_i);
    //FUNCTION_CALL
    array_match_value_prefix_nc(s__a ,s__b );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_match_value_prefix_nc/array_match_value_prefix_nc5/array_match_value_prefix_nc5.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_match_value_prefix_nc/array_match_value_prefix_nc5/array_match_value_prefix_nc5.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/array_match_value_prefix_nc/array_match_value_prefix_nc5/array_match_value_prefix_nc5.c:18:5: error: use of undeclared identifier 'http_method_t'
    http_method_t e_1_i = e_1_i_enum_index % 41;
    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/array_match_value_prefix_nc/array_match_value_prefix_nc5/array_match_value_prefix_nc5.c:20:27: warning: implicit declaration of function 'http_method_buf' is invalid in C99 [-Wimplicit-function-declaration]
    const buffer * s__b = http_method_buf(e_1_i);
                          ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
1 warning and 2 errors generated.

 */
