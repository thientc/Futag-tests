#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "http_kv.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_version_append/http_version_append3/http_version_append3.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/http_version_append/http_version_append3/http_version_append3.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/http_version_append/http_version_append3/http_version_append3.c:22:25: error: use of undeclared identifier 's__b'
    http_version_append(s__b ,q_e__version );
                        ^
1 error generated.

 */
