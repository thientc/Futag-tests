#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(char)+sizeof(size_t)+sizeof(char)+sizeof(size_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    char b__buf;
    memcpy(&b__buf, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_POINTER
    char *const __restrict p_b__buf = & b__buf;
    
    //GEN_BUILTIN
    size_t b_buf_len;
    memcpy(&b_buf_len, pos, sizeof(size_t));
    pos += sizeof(size_t);
    
    //GEN_BUILTIN
    char b__s;
    memcpy(&b__s, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_QUALIFIED
    const char q_b__s = b__s;
    //GEN_POINTER
    const char *const __restrict p_q_b__s = & q_b__s;
    
    //GEN_BUILTIN
    size_t b_s_len;
    memcpy(&b_s_len, pos, sizeof(size_t));
    pos += sizeof(size_t);
    
    //FUNCTION_CALL
    li_tohex_uc(p_b__buf ,b_buf_len ,p_q_b__s ,b_s_len );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_tohex_uc/li_tohex_uc1/li_tohex_uc1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_tohex_uc/li_tohex_uc1/li_tohex_uc1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/li_tohex_uc1-3d7d69.o: in function `LLVMFuzzerTestOneInput':
li_tohex_uc1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x39b): undefined reference to `li_tohex_uc'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
