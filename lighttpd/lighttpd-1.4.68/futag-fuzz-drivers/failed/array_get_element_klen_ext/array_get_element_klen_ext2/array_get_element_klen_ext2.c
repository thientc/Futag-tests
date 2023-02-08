#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "array.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(int)+sizeof(uint32_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(int)+sizeof(uint32_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    int b__ext;
    memcpy(&b__ext, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__ext = b__ext;
    
    //GEN_CSTRING
    char * rstr_key = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_key, 0, dyn_size[0] + 1);
    memcpy(rstr_key, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char * str_key = rstr_key;
    
    //GEN_BUILTIN
    uint32_t b__klen;
    memcpy(&b__klen, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_QUALIFIED
    const uint32_t q_b__klen = b__klen;
    
    //FUNCTION_CALL
    array_get_element_klen_ext(s__a ,q_b__ext ,str_key ,q_b__klen );
    //FREE
    if (rstr_key) {
        free(rstr_key);
        rstr_key = NULL;
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_get_element_klen_ext/array_get_element_klen_ext2/array_get_element_klen_ext2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/array_get_element_klen_ext/array_get_element_klen_ext2/array_get_element_klen_ext2.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/array_get_element_klen_ext/array_get_element_klen_ext2/array_get_element_klen_ext2.c:41:32: error: use of undeclared identifier 's__a'
    array_get_element_klen_ext(s__a ,q_b__ext ,str_key ,q_b__klen );
                               ^
1 error generated.

 */
