#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 3 + 0 + sizeof(unsigned int)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 3 + sizeof(unsigned int))));
    //generate random array of dynamic string sizes
    size_t dyn_size[3];
    srand(time(NULL));
    if(dyn_buffer == 0) dyn_size[0] = dyn_buffer; 
    else dyn_size[0] = rand() % dyn_buffer; 
    size_t remain = dyn_size[0];
    for(size_t i = 1; i< 3 - 1; i++){
        if(dyn_buffer - remain == 0) dyn_size[i] = dyn_buffer - remain;
        else dyn_size[i] = rand() % (dyn_buffer - remain);
        remain += dyn_size[i];
    }
    dyn_size[3 - 1] = dyn_buffer - remain;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_ENUM
    unsigned int e_1_i_enum_index; 
    memcpy(&e_1_i_enum_index, pos, sizeof(unsigned int));
    http_method_t e_1_i = e_1_i_enum_index % 41;
    //GEN_VAR_FUNCTION
    const buffer * s__b = http_method_buf(e_1_i);
    //GEN_CSTRING
    char * rstr_s1 = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_s1, 0, dyn_size[0] + 1);
    memcpy(rstr_s1, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_s1 = rstr_s1;
    
    //GEN_SIZE
    const size_t sz__len1 = (const size_t) dyn_size[0];
    
    //GEN_CSTRING
    char * rstr_s2 = (char *) malloc(dyn_size[1] + 1);
    memset(rstr_s2, 0, dyn_size[1] + 1);
    memcpy(rstr_s2, pos, dyn_size[1] );
    pos += dyn_size[1];
    const char *const str_s2 = rstr_s2;
    
    //GEN_SIZE
    const size_t sz__len2 = (const size_t) dyn_size[1];
    
    //GEN_CSTRING
    char * rstr_s3 = (char *) malloc(dyn_size[2] + 1);
    memset(rstr_s3, 0, dyn_size[2] + 1);
    memcpy(rstr_s3, pos, dyn_size[2] );
    pos += dyn_size[2];
    const char *const str_s3 = rstr_s3;
    
    //GEN_SIZE
    const size_t sz__len3 = (const size_t) dyn_size[2];
    
    //FUNCTION_CALL
    buffer_append_str3(s__b ,str_s1 ,sz__len1 ,str_s2 ,sz__len2 ,str_s3 ,sz__len3 );
    //FREE
    if (rstr_s1) {
        free(rstr_s1);
        rstr_s1 = NULL;
    }
    if (rstr_s2) {
        free(rstr_s2);
        rstr_s2 = NULL;
    }
    if (rstr_s3) {
        free(rstr_s3);
        rstr_s3 = NULL;
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_str3/buffer_append_str32/buffer_append_str32.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_str3/buffer_append_str32/buffer_append_str32.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_append_str3/buffer_append_str32/buffer_append_str32.c:31:5: error: use of undeclared identifier 'http_method_t'
    http_method_t e_1_i = e_1_i_enum_index % 41;
    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_append_str3/buffer_append_str32/buffer_append_str32.c:33:27: warning: implicit declaration of function 'http_method_buf' is invalid in C99 [-Wimplicit-function-declaration]
    const buffer * s__b = http_method_buf(e_1_i);
                          ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
1 warning and 2 errors generated.

 */
