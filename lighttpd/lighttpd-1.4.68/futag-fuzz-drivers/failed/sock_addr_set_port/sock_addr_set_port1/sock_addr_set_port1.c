#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "sock_addr.h"
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "log.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0 + 0 + sizeof(unsigned short)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    unsigned short b__port;
    memcpy(&b__port, pos, sizeof(unsigned short));
    pos += sizeof(unsigned short);
    //GEN_QUALIFIED
    const unsigned short q_b__port = b__port;
    
    //FUNCTION_CALL
    sock_addr_set_port(_saddr ,q_b__port );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o sock_addr.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sock_addr.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sock_addr.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/sock_addr_set_port/sock_addr_set_port1/sock_addr_set_port1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/sock_addr_set_port/sock_addr_set_port1/sock_addr_set_port1.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/sock_addr_set_port/sock_addr_set_port1/sock_addr_set_port1.c:8:
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sock_addr.h:6:
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sys-socket.h:38:13: error: typedef redefinition with different types ('int' vs '__socklen_t' (aka 'unsigned int'))
typedef int socklen_t;
            ^
/usr/include/x86_64-linux-gnu/bits/socket.h:33:21: note: previous definition is here
typedef __socklen_t socklen_t;
                    ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
