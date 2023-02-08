#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "http_kv.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned int)+sizeof(int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__b = http_method_buf(e_1_i);
    //GEN_BUILTIN
    int b__status;
    memcpy(&b__status, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__status = b__status;
    
    //FUNCTION_CALL
    http_status_append(s__b ,q_b__status );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-http_kv.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_kv.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_kv.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_status_append/http_status_append2/http_status_append2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_status_append/http_status_append2/http_status_append2.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_status_append/http_status_append2/http_status_append2.c:28:24: warning: passing 'const buffer *' to parameter of type 'buffer *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    http_status_append(s__b ,q_b__status );
                       ^~~~
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_kv.h:88:33: note: passing argument to parameter 'b' here
void http_status_append(buffer *b, int status);
                                ^
1 warning generated.
/usr/bin/ld: /tmp/http_status_append2-8984d3.o: in function `LLVMFuzzerTestOneInput':
http_status_append2.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1ee): undefined reference to `http_method_buf'
/usr/bin/ld: http_status_append2.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x27e): undefined reference to `http_status_append'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
