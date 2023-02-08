#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "http_kv.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned int)+sizeof(unsigned int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__b = http_method_buf(e_1_i);
    //GEN_ENUM
    unsigned int e__version_enum_index; 
    memcpy(&e__version_enum_index, pos, sizeof(unsigned int));
    http_version_t e__version = e__version_enum_index % 4;
    //GEN_QUALIFIED
    const http_version_t q_e__version = e__version;
    
    //FUNCTION_CALL
    http_version_append(s__b ,q_e__version );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_version_append/http_version_append2/http_version_append2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_version_append/http_version_append2/http_version_append2.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_version_append/http_version_append2/http_version_append2.c:28:25: warning: passing 'const buffer *' to parameter of type 'buffer *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    http_version_append(s__b ,q_e__version );
                        ^~~~
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/http_kv.h:91:34: note: passing argument to parameter 'b' here
void http_version_append(buffer *b, http_version_t version);
                                 ^
1 warning generated.
/usr/bin/ld: /tmp/http_version_append2-9a1289.o: in function `LLVMFuzzerTestOneInput':
http_version_append2.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1ee): undefined reference to `http_method_buf'
/usr/bin/ld: http_version_append2.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x27b): undefined reference to `http_version_append'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
