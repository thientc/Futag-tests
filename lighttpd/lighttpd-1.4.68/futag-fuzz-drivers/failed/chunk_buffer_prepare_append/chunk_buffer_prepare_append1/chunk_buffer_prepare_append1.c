#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "chunk.h"
#include "fdevent.h"
#include "log.h"
#include <sys/stat.h>
#include "sys-mmap.h"
#include "sys-setjmp.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/uio.h>
#include <sys/sendfile.h>

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(size_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_VAR_FUNCTION
    buffer * s__b = chunk_buffer_acquire();
    //GEN_BUILTIN
    size_t b_sz;
    memcpy(&b_sz, pos, sizeof(size_t));
    pos += sizeof(size_t);
    
    //FUNCTION_CALL
    chunk_buffer_prepare_append(s__b ,b_sz );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-chunk.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/chunk.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/chunk.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/chunk_buffer_prepare_append/chunk_buffer_prepare_append1/chunk_buffer_prepare_append1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/chunk_buffer_prepare_append/chunk_buffer_prepare_append1/chunk_buffer_prepare_append1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/chunk_buffer_prepare_append1-00efb2.o: in function `LLVMFuzzerTestOneInput':
chunk_buffer_prepare_append1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x16a): undefined reference to `chunk_buffer_acquire'
/usr/bin/ld: chunk_buffer_prepare_append1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1dc): undefined reference to `chunk_buffer_prepare_append'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
