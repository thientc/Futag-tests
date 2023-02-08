#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "ck.h"
#include <errno.h>

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(void)+sizeof(rsize_t)+sizeof(rsize_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    void b__s;
    memcpy(&b__s, pos, sizeof(void));
    pos += sizeof(void);
    //GEN_POINTER
    void *const p_b__s = & b__s;
    
    //GEN_BUILTIN
    rsize_t b__smax;
    memcpy(&b__smax, pos, sizeof(rsize_t));
    pos += sizeof(rsize_t);
    //GEN_QUALIFIED
    const rsize_t q_b__smax = b__smax;
    
    //GEN_BUILTIN
    rsize_t b_n;
    memcpy(&b_n, pos, sizeof(rsize_t));
    pos += sizeof(rsize_t);
    
    //FUNCTION_CALL
    ck_memclear_s(p_b__s ,q_b__smax ,b_n );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o ck.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ck.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ck.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_memclear_s/ck_memclear_s1/ck_memclear_s1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_memclear_s/ck_memclear_s1/ck_memclear_s1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/ck_memclear_s/ck_memclear_s1/ck_memclear_s1.c:15:10: error: variable has incomplete type 'void'
    void b__s;
         ^
1 error generated.

 */
