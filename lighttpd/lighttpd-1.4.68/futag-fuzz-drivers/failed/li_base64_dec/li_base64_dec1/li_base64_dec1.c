#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "base64.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(unsigned char)+sizeof(size_t)+sizeof(unsigned int)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(unsigned char)+sizeof(size_t)+sizeof(unsigned int))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    unsigned char b__result;
    memcpy(&b__result, pos, sizeof(unsigned char));
    pos += sizeof(unsigned char);
    //GEN_POINTER
    unsigned char *const p_b__result = & b__result;
    
    //GEN_BUILTIN
    size_t b__out_length;
    memcpy(&b__out_length, pos, sizeof(size_t));
    pos += sizeof(size_t);
    //GEN_QUALIFIED
    const size_t q_b__out_length = b__out_length;
    
    //GEN_CSTRING
    char * rstr_in = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_in, 0, dyn_size[0] + 1);
    memcpy(rstr_in, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_in = rstr_in;
    
    //GEN_SIZE
    const size_t sz__in_length = (const size_t) dyn_size[0];
    
    //GEN_ENUM
    unsigned int e__charset_enum_index; 
    memcpy(&e__charset_enum_index, pos, sizeof(unsigned int));
    base64_charset e__charset = e__charset_enum_index % 2;
    //GEN_QUALIFIED
    const base64_charset q_e__charset = e__charset;
    
    //FUNCTION_CALL
    li_base64_dec(p_b__result ,q_b__out_length ,str_in ,sz__in_length ,q_e__charset );
    //FREE
    if (rstr_in) {
        free(rstr_in);
        rstr_in = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_base64_dec/li_base64_dec1/li_base64_dec1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_base64_dec/li_base64_dec1/li_base64_dec1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/li_base64_dec1-4ddcd7.o: in function `LLVMFuzzerTestOneInput':
li_base64_dec1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x450): undefined reference to `li_base64_dec'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
