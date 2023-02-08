#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "array.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(uint32_t)+sizeof(uint32_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(uint32_t)+sizeof(uint32_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    uint32_t b_1_n;
    memcpy(&b_1_n, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_VAR_FUNCTION
    array * s__a = array_init(b_1_n);
    //GEN_CSTRING
    char * rstr_v = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_v, 0, dyn_size[0] + 1);
    memcpy(rstr_v, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_v = rstr_v;
    
    //GEN_BUILTIN
    uint32_t b__vlen;
    memcpy(&b__vlen, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_QUALIFIED
    const uint32_t q_b__vlen = b__vlen;
    
    //FUNCTION_CALL
    array_insert_value(s__a ,str_v ,q_b__vlen );
    //FREE
    if (rstr_v) {
        free(rstr_v);
        rstr_v = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_insert_value/array_insert_value1/array_insert_value1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_insert_value/array_insert_value1/array_insert_value1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/array_insert_value1-d022b9.o: in function `LLVMFuzzerTestOneInput':
array_insert_value1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x25b): undefined reference to `array_init'
/usr/bin/ld: array_insert_value1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x3f2): undefined reference to `array_insert_value'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
