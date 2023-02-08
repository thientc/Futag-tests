#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "array.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(uint32_t)+sizeof(uint32_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    uint32_t b_1_n;
    memcpy(&b_1_n, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_VAR_FUNCTION
    array * s__dst = array_init(b_1_n);
    
    //GEN_BUILTIN
    uint32_t b_2_n;
    memcpy(&b_2_n, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_VAR_FUNCTION
    array * s__src = array_init(b_2_n);
    //FUNCTION_CALL
    array_copy_array(s__dst ,s__src );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_copy_array/array_copy_array1/array_copy_array1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_copy_array/array_copy_array1/array_copy_array1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/array_copy_array1-1b76bd.o: in function `LLVMFuzzerTestOneInput':
array_copy_array1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1eb): undefined reference to `array_init'
/usr/bin/ld: array_copy_array1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x268): undefined reference to `array_init'
/usr/bin/ld: array_copy_array1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x282): undefined reference to `array_copy_array'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
