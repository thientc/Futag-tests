#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "buffer.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(intmax_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(intmax_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_CSTRING
    char * str_buf = (char *) malloc(dyn_size[0] + 1);
    memset(str_buf, 0, dyn_size[0] + 1);
    memcpy(str_buf, pos, dyn_size[0] );
    pos += dyn_size[0];
    
    //GEN_SIZE
    size_t sz_buf_len = (size_t) dyn_size[0];
    
    //GEN_BUILTIN
    intmax_t b_val;
    memcpy(&b_val, pos, sizeof(intmax_t));
    pos += sizeof(intmax_t);
    
    //FUNCTION_CALL
    li_itostrn(str_buf ,sz_buf_len ,b_val );
    //FREE
    if (str_buf) {
        free(str_buf);
        str_buf = NULL;
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_itostrn/li_itostrn1/li_itostrn1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/li_itostrn/li_itostrn1/li_itostrn1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/li_itostrn1-990cfd.o: in function `LLVMFuzzerTestOneInput':
li_itostrn1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x36a): undefined reference to `li_itostrn'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
