#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "burl.h"
#include "base64.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(int)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(int))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_VAR_FUNCTION
    buffer * s__b = chunk_buffer_acquire();
    //GEN_CSTRING
    char * rstr_str = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_str, 0, dyn_size[0] + 1);
    memcpy(rstr_str, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_str = rstr_str;
    
    //GEN_SIZE
    const size_t sz__len = (const size_t) dyn_size[0];
    
    //GEN_BUILTIN
    int b__flags;
    memcpy(&b__flags, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__flags = b__flags;
    
    //FUNCTION_CALL
    burl_append(s__b ,str_str ,sz__len ,q_b__flags );
    //FREE
    if (rstr_str) {
        free(rstr_str);
        rstr_str = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-burl.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/burl.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/burl.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/burl_append/burl_append1/burl_append1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/burl_append/burl_append1/burl_append1.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/burl_append/burl_append1/burl_append1.c:21:21: warning: implicit declaration of function 'chunk_buffer_acquire' is invalid in C99 [-Wimplicit-function-declaration]
    buffer * s__b = chunk_buffer_acquire();
                    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/burl_append/burl_append1/burl_append1.c:21:14: warning: incompatible integer to pointer conversion initializing 'buffer *' with an expression of type 'int' [-Wint-conversion]
    buffer * s__b = chunk_buffer_acquire();
             ^      ~~~~~~~~~~~~~~~~~~~~~~
2 warnings generated.
/usr/bin/ld: /tmp/burl_append1-1328f8.o: in function `LLVMFuzzerTestOneInput':
burl_append1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1e4): undefined reference to `chunk_buffer_acquire'
/usr/bin/ld: burl_append1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x3ac): undefined reference to `burl_append'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
