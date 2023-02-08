#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "fdlog.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "fdevent.h"
#include "log.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(int)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    int b__fd;
    memcpy(&b__fd, pos, sizeof(int));
    pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__fd = b__fd;
    
    //FUNCTION_CALL
    fdlog_pipe_serrh(q_b__fd );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-fdlog_maint.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/fdlog_maint.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/fdlog_maint.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_pipe_serrh/fdlog_pipe_serrh1/fdlog_pipe_serrh1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_pipe_serrh/fdlog_pipe_serrh1/fdlog_pipe_serrh1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/fdlog_pipe_serrh1-f02484.o: in function `LLVMFuzzerTestOneInput':
fdlog_pipe_serrh1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1e5): undefined reference to `fdlog_pipe_serrh'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
