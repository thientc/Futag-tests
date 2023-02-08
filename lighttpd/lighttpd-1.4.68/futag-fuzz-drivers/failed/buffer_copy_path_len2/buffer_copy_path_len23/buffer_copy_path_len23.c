#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(char)+sizeof(char)+sizeof(size_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    char b__s1;
    memcpy(&b__s1, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_QUALIFIED
    const char q_b__s1 = b__s1;
    //GEN_POINTER
    const char *const __restrict p_q_b__s1 = & q_b__s1;
    
    //GEN_SIZE
    size_t sz_len1 = (size_t) dyn_size[-1];
    
    //GEN_BUILTIN
    char b__s2;
    memcpy(&b__s2, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_QUALIFIED
    const char q_b__s2 = b__s2;
    //GEN_POINTER
    const char *const __restrict p_q_b__s2 = & q_b__s2;
    
    //GEN_BUILTIN
    size_t b_len2;
    memcpy(&b_len2, pos, sizeof(size_t));
    pos += sizeof(size_t);
    
    //FUNCTION_CALL
    buffer_copy_path_len2(s__b ,p_q_b__s1 ,sz_len1 ,p_q_b__s2 ,b_len2 );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_copy_path_len2/buffer_copy_path_len23/buffer_copy_path_len23.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_copy_path_len2/buffer_copy_path_len23/buffer_copy_path_len23.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_copy_path_len2/buffer_copy_path_len23/buffer_copy_path_len23.c:24:31: error: use of undeclared identifier 'dyn_size'
    size_t sz_len1 = (size_t) dyn_size[-1];
                              ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
