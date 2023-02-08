#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "base64.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(char)+sizeof(size_t)+sizeof(unsigned char)+sizeof(size_t)+sizeof(unsigned int)+sizeof(int)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    char b__out;
    memcpy(&b__out, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_POINTER
    char *const __restrict p_b__out = & b__out;
    
    //GEN_BUILTIN
    size_t b__out_length;
    memcpy(&b__out_length, pos, sizeof(size_t));
    pos += sizeof(size_t);
    //GEN_QUALIFIED
    const size_t q_b__out_length = b__out_length;
    
    //GEN_BUILTIN
    unsigned char b__in;
    memcpy(&b__in, pos, sizeof(unsigned char));
    pos += sizeof(unsigned char);
    //GEN_QUALIFIED
    const unsigned char q_b__in = b__in;
    //GEN_POINTER
    const unsigned char *const __restrict p_q_b__in = & q_b__in;
    
    //GEN_BUILTIN
    size_t b__in_length;
    memcpy(&b__in_length, pos, sizeof(size_t));
    pos += sizeof(size_t);
    //GEN_QUALIFIED
    const size_t q_b__in_length = b__in_length;
    
    //GEN_ENUM
    unsigned int e__charset_enum_index; 
    memcpy(&e__charset_enum_index, pos, sizeof(unsigned int));
    base64_charset e__charset = e__charset_enum_index % 2;
    //GEN_QUALIFIED
    const base64_charset q_e__charset = e__charset;
    
    //GEN_BUILTIN
    int b__pad;
    memcpy(&b__pad, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__pad = b__pad;
    
    //FUNCTION_CALL
    li_base64_enc(p_b__out ,q_b__out_length ,p_q_b__in ,q_b__in_length ,q_e__charset ,q_b__pad );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-base64.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/base64.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/base64.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_base64_enc/li_base64_enc1/li_base64_enc1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_base64_enc/li_base64_enc1/li_base64_enc1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/li_base64_enc1-266948.o: in function `LLVMFuzzerTestOneInput':
li_base64_enc1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x4b5): undefined reference to `li_base64_enc'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
