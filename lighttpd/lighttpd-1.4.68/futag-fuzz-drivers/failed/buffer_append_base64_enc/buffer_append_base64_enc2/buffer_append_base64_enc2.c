#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "base64.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(unsigned int)+sizeof(unsigned int)+sizeof(int)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(unsigned int)+sizeof(unsigned int)+sizeof(int))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__out = http_method_buf(e_1_i);
    //GEN_CSTRING
    unsigned char * rstr_in = (unsigned char *) malloc(dyn_size[0] + 1);
    memset(rstr_in, 0, dyn_size[0] + 1);
    memcpy(rstr_in, pos, dyn_size[0] );
    pos += dyn_size[0];
    const unsigned char * str_in = rstr_in;
    
    //GEN_SIZE
    size_t sz_in_length = (size_t) dyn_size[0];
    
    //GEN_ENUM
    unsigned int e_charset_enum_index; 
    memcpy(&e_charset_enum_index, pos, sizeof(unsigned int));
    base64_charset e_charset = e_charset_enum_index % 2;
    
    //GEN_BUILTIN
    int b_pad;
    memcpy(&b_pad, pos, sizeof(int));
    pos += sizeof(int);
    
    //FUNCTION_CALL
    char * futag_target = buffer_append_base64_enc(s__out ,str_in ,sz_in_length ,e_charset ,b_pad );
    if(futag_target){
        free(futag_target);
        futag_target = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_base64_enc/buffer_append_base64_enc2/buffer_append_base64_enc2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_base64_enc/buffer_append_base64_enc2/buffer_append_base64_enc2.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_append_base64_enc/buffer_append_base64_enc2/buffer_append_base64_enc2.c:22:5: error: use of undeclared identifier 'http_method_t'
    http_method_t e_1_i = e_1_i_enum_index % 41;
    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_append_base64_enc/buffer_append_base64_enc2/buffer_append_base64_enc2.c:24:29: warning: implicit declaration of function 'http_method_buf' is invalid in C99 [-Wimplicit-function-declaration]
    const buffer * s__out = http_method_buf(e_1_i);
                            ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
1 warning and 2 errors generated.

 */
