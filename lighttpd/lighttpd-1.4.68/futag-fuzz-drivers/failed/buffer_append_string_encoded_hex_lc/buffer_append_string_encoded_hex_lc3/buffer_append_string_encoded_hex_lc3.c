#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(char)+sizeof(size_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    char b__s;
    memcpy(&b__s, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_QUALIFIED
    const char q_b__s = b__s;
    //GEN_POINTER
    const char *const __restrict p_q_b__s = & q_b__s;
    
    //GEN_BUILTIN
    size_t b_len;
    memcpy(&b_len, pos, sizeof(size_t));
    pos += sizeof(size_t);
    
    //FUNCTION_CALL
    buffer_append_string_encoded_hex_lc(s__b ,p_q_b__s ,b_len );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_string_encoded_hex_lc/buffer_append_string_encoded_hex_lc3/buffer_append_string_encoded_hex_lc3.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_string_encoded_hex_lc/buffer_append_string_encoded_hex_lc3/buffer_append_string_encoded_hex_lc3.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_append_string_encoded_hex_lc/buffer_append_string_encoded_hex_lc3/buffer_append_string_encoded_hex_lc3.c:29:41: error: use of undeclared identifier 's__b'
    buffer_append_string_encoded_hex_lc(s__b ,p_q_b__s ,b_len );
                                        ^
1 error generated.

 */
