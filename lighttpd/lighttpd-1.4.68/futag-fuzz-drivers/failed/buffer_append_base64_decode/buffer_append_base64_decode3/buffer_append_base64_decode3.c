#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "base64.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(unsigned int)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(unsigned int))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_CSTRING
    char * rstr_in = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_in, 0, dyn_size[0] + 1);
    memcpy(rstr_in, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char * str_in = rstr_in;
    
    //GEN_SIZE
    size_t sz_in_length = (size_t) dyn_size[0];
    
    //GEN_ENUM
    unsigned int e_charset_enum_index; 
    memcpy(&e_charset_enum_index, pos, sizeof(unsigned int));
    base64_charset e_charset = e_charset_enum_index % 2;
    
    //FUNCTION_CALL
    unsigned char * futag_target = buffer_append_base64_decode(s__out ,str_in ,sz_in_length ,e_charset );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_base64_decode/buffer_append_base64_decode3/buffer_append_base64_decode3.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/buffer_append_base64_decode/buffer_append_base64_decode3/buffer_append_base64_decode3.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_append_base64_decode/buffer_append_base64_decode3/buffer_append_base64_decode3.c:35:64: error: use of undeclared identifier 's__out'; did you mean 'stdout'?
    unsigned char * futag_target = buffer_append_base64_decode(s__out ,str_in ,sz_in_length ,e_charset );
                                                               ^~~~~~
                                                               stdout
/usr/include/stdio.h:144:14: note: 'stdout' declared here
extern FILE *stdout;            /* Standard output stream.  */
             ^
1 error generated.

 */
