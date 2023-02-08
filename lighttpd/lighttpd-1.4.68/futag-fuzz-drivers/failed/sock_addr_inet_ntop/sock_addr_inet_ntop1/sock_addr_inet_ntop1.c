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
    if (Fuzz_Size < 0 + 0 + sizeof(char)+sizeof(socklen_t)) return 0;
    uint8_t * pos = Fuzz_Data;
    
    //GEN_BUILTIN
    char b__buf;
    memcpy(&b__buf, pos, sizeof(char));
    pos += sizeof(char);
    //GEN_POINTER
    char *const __restrict p_b__buf = & b__buf;
    
    //GEN_BUILTIN
    socklen_t b_sz;
    memcpy(&b_sz, pos, sizeof(socklen_t));
    pos += sizeof(socklen_t);
    
    //FUNCTION_CALL
    sock_addr_inet_ntop(_saddr ,p_b__buf ,b_sz );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/sock_addr_inet_ntop/sock_addr_inet_ntop1/sock_addr_inet_ntop1.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/sock_addr_inet_ntop/sock_addr_inet_ntop1/sock_addr_inet_ntop1.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/sock_addr_inet_ntop/sock_addr_inet_ntop1/sock_addr_inet_ntop1.c:8:
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
