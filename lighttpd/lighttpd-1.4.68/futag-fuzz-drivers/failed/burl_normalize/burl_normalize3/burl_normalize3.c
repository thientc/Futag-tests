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
    if (Fuzz_Size < 0 + 0 + sizeof(int)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_VAR_FUNCTION
    buffer * s__b = chunk_buffer_acquire();
    
    //GEN_BUILTIN
    int b_flags;
    memcpy(&b_flags, pos, sizeof(int));
    pos += sizeof(int);
    
    //FUNCTION_CALL
    burl_normalize(s__b ,s__t ,b_flags );
    //FREE
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/burl_normalize/burl_normalize3/burl_normalize3.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/burl_normalize/burl_normalize3/burl_normalize3.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/burl_normalize/burl_normalize3/burl_normalize3.c:16:21: warning: implicit declaration of function 'chunk_buffer_acquire' is invalid in C99 [-Wimplicit-function-declaration]
    buffer * s__b = chunk_buffer_acquire();
                    ^
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/burl_normalize/burl_normalize3/burl_normalize3.c:16:14: warning: incompatible integer to pointer conversion initializing 'buffer *' with an expression of type 'int' [-Wint-conversion]
    buffer * s__b = chunk_buffer_acquire();
             ^      ~~~~~~~~~~~~~~~~~~~~~~
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/burl_normalize/burl_normalize3/burl_normalize3.c:24:26: error: use of undeclared identifier 's__t'; did you mean 's__b'?
    burl_normalize(s__b ,s__t ,b_flags );
                         ^~~~
                         s__b
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/burl_normalize/burl_normalize3/burl_normalize3.c:16:14: note: 's__b' declared here
    buffer * s__b = chunk_buffer_acquire();
             ^
2 warnings and 1 error generated.

 */
