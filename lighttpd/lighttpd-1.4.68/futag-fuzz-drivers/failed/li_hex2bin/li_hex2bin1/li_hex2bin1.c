#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(unsigned char)+sizeof(size_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(unsigned char)+sizeof(size_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    unsigned char b__bin;
    memcpy(&b__bin, pos, sizeof(unsigned char));
    pos += sizeof(unsigned char);
    //GEN_POINTER
    unsigned char *const p_b__bin = & b__bin;
    
    //GEN_BUILTIN
    size_t b__binlen;
    memcpy(&b__binlen, pos, sizeof(size_t));
    pos += sizeof(size_t);
    //GEN_QUALIFIED
    const size_t q_b__binlen = b__binlen;
    
    //GEN_CSTRING
    char * rstr_hexstr = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_hexstr, 0, dyn_size[0] + 1);
    memcpy(rstr_hexstr, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_hexstr = rstr_hexstr;
    
    //GEN_SIZE
    const size_t sz__len = (const size_t) dyn_size[0];
    
    //FUNCTION_CALL
    li_hex2bin(p_b__bin ,q_b__binlen ,str_hexstr ,sz__len );
    //FREE
    if (rstr_hexstr) {
        free(rstr_hexstr);
        rstr_hexstr = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_hex2bin/li_hex2bin1/li_hex2bin1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_hex2bin/li_hex2bin1/li_hex2bin1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/li_hex2bin1-09aec8.o: in function `LLVMFuzzerTestOneInput':
li_hex2bin1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x3cd): undefined reference to `li_hex2bin'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
