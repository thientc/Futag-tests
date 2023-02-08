#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 2 + 0) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 2)));
    //generate random array of dynamic string sizes
    size_t dyn_size[2];
    srand(time(NULL));
    if(dyn_buffer == 0) dyn_size[0] = dyn_buffer; 
    else dyn_size[0] = rand() % dyn_buffer; 
    size_t remain = dyn_size[0];
    for(size_t i = 1; i< 2 - 1; i++){
        if(dyn_buffer - remain == 0) dyn_size[i] = dyn_buffer - remain;
        else dyn_size[i] = rand() % (dyn_buffer - remain);
        remain += dyn_size[i];
    }
    dyn_size[2 - 1] = dyn_buffer - remain;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_CSTRING
    char * rstr_a = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_a, 0, dyn_size[0] + 1);
    memcpy(rstr_a, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_a = rstr_a;
    
    //GEN_SIZE
    const size_t sz__alen = (const size_t) dyn_size[0];
    
    //GEN_CSTRING
    char * rstr_b = (char *) malloc(dyn_size[1] + 1);
    memset(rstr_b, 0, dyn_size[1] + 1);
    memcpy(rstr_b, pos, dyn_size[1] );
    pos += dyn_size[1];
    const char *const str_b = rstr_b;
    
    //GEN_SIZE
    const size_t sz__blen = (const size_t) dyn_size[1];
    
    //FUNCTION_CALL
    buffer_eq_icase_ss(str_a ,sz__alen ,str_b ,sz__blen );
    //FREE
    if (rstr_a) {
        free(rstr_a);
        rstr_a = NULL;
    }
    if (rstr_b) {
        free(rstr_b);
        rstr_b = NULL;
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/succeeded/buffer_eq_icase_ss/buffer_eq_icase_ss1/buffer_eq_icase_ss1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/succeeded/buffer_eq_icase_ss/buffer_eq_icase_ss1/buffer_eq_icase_ss1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/buffer_eq_icase_ss/buffer_eq_icase_ss1/buffer_eq_icase_ss1.c:48:5: warning: ignoring return value of function declared with pure attribute [-Wunused-value]
    buffer_eq_icase_ss(str_a ,sz__alen ,str_b ,sz__blen );
    ^~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning generated.

 */
