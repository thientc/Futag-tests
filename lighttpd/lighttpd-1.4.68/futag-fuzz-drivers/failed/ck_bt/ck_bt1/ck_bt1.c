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
    if (Fuzz_Size < 1 + 1) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 1 + 1)));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    size_t file_buffer = (size_t) ((Fuzz_Size - dyn_buffer - (1)));
    //generate random array of dynamic file sizes
    size_t file_size[1];
    file_size[0] = file_buffer;
    //end of generation random array of dynamic file sizes
    uint8_t * pos = Fuzz_Data;
    //GEN_INPUT_FILE
    const char* f_filename = "futag_input_file_0";
    FILE * fp_0 = fopen(f_filename,"w");
    if (fp_0  == NULL) {
        return 0;
    }
    fwrite(pos, 1, file_size[0], fp_0);
    fclose(fp_0);
    pos += file_size[0];
    
    //GEN_SIZE
    unsigned int sz_line = (unsigned int) dyn_size[-1];
    
    //GEN_CSTRING
    char * rstr_msg = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_msg, 0, dyn_size[0] + 1);
    memcpy(rstr_msg, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char * str_msg = rstr_msg;
    
    //FUNCTION_CALL
    ck_bt(f_filename ,sz_line ,str_msg );
    //FREE
    if (rstr_msg) {
        free(rstr_msg);
        rstr_msg = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_bt/ck_bt1/ck_bt1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/ck_bt/ck_bt1/ck_bt1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/ck_bt1-7f57c4.o: in function `LLVMFuzzerTestOneInput':
ck_bt1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x467): undefined reference to `ck_bt'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
