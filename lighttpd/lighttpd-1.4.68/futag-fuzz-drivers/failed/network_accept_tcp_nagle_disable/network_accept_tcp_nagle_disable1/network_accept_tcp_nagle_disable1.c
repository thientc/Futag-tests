#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "network.h"
#include "base.h"
#include "fdevent.h"
#include "log.h"
#include "connections.h"
#include "plugin.h"
#include "network_write.h"
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

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
    network_accept_tcp_nagle_disable(q_b__fd );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o lighttpd-network.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/network.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/network.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/network_accept_tcp_nagle_disable/network_accept_tcp_nagle_disable1/network_accept_tcp_nagle_disable1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/network_accept_tcp_nagle_disable/network_accept_tcp_nagle_disable1/network_accept_tcp_nagle_disable1.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/network_accept_tcp_nagle_disable/network_accept_tcp_nagle_disable1/network_accept_tcp_nagle_disable1.c:9:
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/base.h:5:
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sys-time.h:37:1: error: static declaration of 'timegm' follows non-static declaration
timegm (const struct tm * const tm);
^
/usr/include/time.h:249:15: note: previous declaration is here
extern time_t timegm (struct tm *__tp) __THROW;
              ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
