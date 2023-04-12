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
#include "SigProc_FIX.h"
#include "resampler_private.h"
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

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + 0 * sizeof(int) + 0 * sizeof(int) + 0 * sizeof(short) + 0 * sizeof(short) + sizeof(opus_int32)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    opus_int32 * a_S = (opus_int32 *) malloc(sizeof(int) * 0);
    memcpy(a_S, futag_pos, 0 * sizeof(int));
    futag_pos += 0 * sizeof(int);
    
    //GEN_ARRAY
    opus_int32 * a_out_Q8 = (opus_int32 *) malloc(sizeof(int) * 0);
    memcpy(a_out_Q8, futag_pos, 0 * sizeof(int));
    futag_pos += 0 * sizeof(int);
    
    //GEN_ARRAY
    const opus_int16 * a_in = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_in, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_ARRAY
    const opus_int16 * a_A_Q14 = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_A_Q14, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_BUILTIN
    opus_int32 b_len;
    memcpy(&b_len, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    
    //FUNCTION_CALL
    silk_resampler_private_AR2(a_S ,a_out_Q8 ,a_in ,a_A_Q14 ,b_len );
    //FREE
    if (a_S) {
        free( a_S);
        a_S = NULL;
    }
    if (a_out_Q8) {
        free( a_out_Q8);
        a_out_Q8 = NULL;
    }
    if (a_in) {
        free( a_in);
        a_in = NULL;
    }
    if (a_A_Q14) {
        free( a_A_Q14);
        a_A_Q14 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/resampler_private_AR2.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/resampler_private_AR2.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/resampler_private_AR2.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_resampler_private_AR2/silk_resampler_private_AR21/silk_resampler_private_AR21.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_resampler_private_AR2/silk_resampler_private_AR21/silk_resampler_private_AR21.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_resampler_private_AR2/silk_resampler_private_AR21/silk_resampler_private_AR21.c:42:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_in, futag_pos, 0 * sizeof(short));
           ^~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_resampler_private_AR2/silk_resampler_private_AR21/silk_resampler_private_AR21.c:47:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_A_Q14, futag_pos, 0 * sizeof(short));
           ^~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_resampler_private_AR2/silk_resampler_private_AR21/silk_resampler_private_AR21.c:67:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_in);
              ^~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_resampler_private_AR2/silk_resampler_private_AR21/silk_resampler_private_AR21.c:71:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_A_Q14);
              ^~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
4 warnings generated.

 */
