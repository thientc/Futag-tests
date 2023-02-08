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
    if (Fuzz_Size < 0 + 0 + sizeof(unix_time64_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    //GEN_BUILTIN
    unix_time64_t b__ts;
    memcpy(&b__ts, pos, sizeof(unix_time64_t));
    pos += sizeof(unix_time64_t);
    //GEN_QUALIFIED
    const unix_time64_t q_b__ts = b__ts;
    
    //FUNCTION_CALL
    fdlog_pipes_restart(q_b__ts );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_pipes_restart/fdlog_pipes_restart1/fdlog_pipes_restart1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/fdlog_pipes_restart/fdlog_pipes_restart1/fdlog_pipes_restart1.out 
 */

// Error log:
/* 
/usr/bin/ld: /tmp/fdlog_pipes_restart1-7421fe.o: in function `LLVMFuzzerTestOneInput':
fdlog_pipes_restart1.c:(.text.LLVMFuzzerTestOneInput[LLVMFuzzerTestOneInput]+0x1cd): undefined reference to `fdlog_pipes_restart'
clang-14: error: linker command failed with exit code 1 (use -v to see invocation)

 */
