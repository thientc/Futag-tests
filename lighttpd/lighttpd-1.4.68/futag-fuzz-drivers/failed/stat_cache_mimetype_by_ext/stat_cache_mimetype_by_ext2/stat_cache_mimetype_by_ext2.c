#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "first.h"
#include "stat_cache.h"
#include "log.h"
#include "fdevent.h"
#include "http_etag.h"
#include "algo_splaytree.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/inotify.h>

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 1 + 0 + sizeof(uint32_t)) return 0;
    size_t dyn_buffer = (size_t) ((Fuzz_Size - ( 0 + 1 + sizeof(uint32_t))));
    //generate random array of dynamic string sizes
    size_t dyn_size[1];
    dyn_size[0] = dyn_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * pos = Fuzz_Data;
    
    //GEN_CSTRING
    char * rstr_name = (char *) malloc(dyn_size[0] + 1);
    memset(rstr_name, 0, dyn_size[0] + 1);
    memcpy(rstr_name, pos, dyn_size[0] );
    pos += dyn_size[0];
    const char *const str_name = rstr_name;
    
    //GEN_BUILTIN
    uint32_t b__nlen;
    memcpy(&b__nlen, pos, sizeof(uint32_t));
    pos += sizeof(uint32_t);
    //GEN_QUALIFIED
    const uint32_t q_b__nlen = b__nlen;
    
    //FUNCTION_CALL
    stat_cache_mimetype_by_ext(s__mimetypes ,str_name ,q_b__nlen );
    //FREE
    if (rstr_name) {
        free(rstr_name);
        rstr_name = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -DHAVE_VERSIONSTAMP_H -DLIBRARY_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/lib\" -DSBIN_DIR=\"/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-install/sbin\" -I. -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src -I.. -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o t_test_mod-stat_cache.o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/stat_cache.c
location: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src
file: /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/stat_cache.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/ -I/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-build/src/../  /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/stat_cache_mimetype_by_ext/stat_cache_mimetype_by_ext2/stat_cache_mimetype_by_ext2.c -o /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/futag-fuzz-drivers/failed/stat_cache_mimetype_by_ext/stat_cache_mimetype_by_ext2/stat_cache_mimetype_by_ext2.out 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/.futag-fuzz-drivers/stat_cache_mimetype_by_ext/stat_cache_mimetype_by_ext2/stat_cache_mimetype_by_ext2.c:8:
In file included from /home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/stat_cache.h:6:
/home/futag/Futag-tests/lighttpd/lighttpd-1.4.68/src/sys-time.h:37:1: error: static declaration of 'timegm' follows non-static declaration
timegm (const struct tm * const tm);
^
/usr/include/time.h:249:15: note: previous declaration is here
extern time_t timegm (struct tm *__tp) __THROW;
              ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
2 errors generated.

 */
