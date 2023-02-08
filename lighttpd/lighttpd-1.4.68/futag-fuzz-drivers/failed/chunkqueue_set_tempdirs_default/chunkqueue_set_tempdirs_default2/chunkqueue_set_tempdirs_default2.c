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
    if (Fuzz_Size < 0 + 0 + sizeof(off_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    off_t b_upload_temp_file_size;
    memcpy(&b_upload_temp_file_size, pos, sizeof(off_t));
    pos += sizeof(off_t);
    
    //FUNCTION_CALL
    chunkqueue_set_tempdirs_default(s__tempdirs ,b_upload_temp_file_size );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/chunkqueue_set_tempdirs_default/chunkqueue_set_tempdirs_default2/chunkqueue_set_tempdirs_default2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/chunkqueue_set_tempdirs_default/chunkqueue_set_tempdirs_default2/chunkqueue_set_tempdirs_default2.out 
 */

// Error log:
/* 
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/chunkqueue_set_tempdirs_default/chunkqueue_set_tempdirs_default2/chunkqueue_set_tempdirs_default2.c:30:37: error: use of undeclared identifier 's__tempdirs'
    chunkqueue_set_tempdirs_default(s__tempdirs ,b_upload_temp_file_size );
                                    ^
1 error generated.

 */
