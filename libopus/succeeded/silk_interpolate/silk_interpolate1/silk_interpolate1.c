#define VAR_ARRAYS 1
#define USE_ALLOCA 1
#define NONTHREADSAFE_PSEUDOSTACK 1
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "config.h"
#include "main.h"
#include "mathops.h"
#include "opus_private.h"
#include "opus_projection.h"
#include "mapping_matrix.h"
#include "stack_alloc.h"
#include <stdarg.h>
#include "celt.h"
#include "opus.h"
#include "modes.h"
#include "API.h"
#include "float_cast.h"
#include "os_support.h"
#include "structs.h"
#include "opus_multistream.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + 16 * sizeof(short) + 16 * sizeof(short) + 16 * sizeof(short) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    opus_int16 * a_xi = (opus_int16 *) malloc(sizeof(short) * 16);
    memcpy(a_xi, futag_pos, 16 * sizeof(short));
    futag_pos += 16 * sizeof(short);
    
    //GEN_ARRAY
    const opus_int16 * a_x0 = (const opus_int16 *) malloc(sizeof(short) * 16);
    memcpy(a_x0, futag_pos, 16 * sizeof(short));
    futag_pos += 16 * sizeof(short);
    
    //GEN_ARRAY
    const opus_int16 * a_x1 = (const opus_int16 *) malloc(sizeof(short) * 16);
    memcpy(a_x1, futag_pos, 16 * sizeof(short));
    futag_pos += 16 * sizeof(short);
    
    //GEN_BUILTIN
    int b__ifact_Q2;
    memcpy(&b__ifact_Q2, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__ifact_Q2 = b__ifact_Q2;
    
    //GEN_BUILTIN
    int b__d;
    memcpy(&b__d, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__d = b__d;
    
    //FUNCTION_CALL
    silk_interpolate(a_xi ,a_x0 ,a_x1 ,q_b__ifact_Q2 ,q_b__d );
    //FREE
    if (a_xi) {
        free( a_xi);
        a_xi = NULL;
    }
    if (a_x0) {
        free( a_x0);
        a_x0 = NULL;
    }
    if (a_x1) {
        free( a_x1);
        a_x1 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/interpolate.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/interpolate.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/interpolate.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_interpolate/silk_interpolate1/silk_interpolate1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_interpolate/silk_interpolate1/silk_interpolate1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_interpolate/silk_interpolate1/silk_interpolate1.c:37:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_x0, futag_pos, 16 * sizeof(short));
           ^~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_interpolate/silk_interpolate1/silk_interpolate1.c:42:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_x1, futag_pos, 16 * sizeof(short));
           ^~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_interpolate/silk_interpolate1/silk_interpolate1.c:67:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_x0);
              ^~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_interpolate/silk_interpolate1/silk_interpolate1.c:71:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_x1);
              ^~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
4 warnings generated.

 */
