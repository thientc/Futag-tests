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
#include "mdct.h"
#include "bands.h"
#include "quant_bands.h"
#include "pitch.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_int32) + 0 * sizeof(short) + 0 * sizeof(short) + 0 * sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_int32 b__ratio_Q14;
    memcpy(&b__ratio_Q14, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_POINTER
    opus_int32 * p_b__ratio_Q14 = & b__ratio_Q14;
    
    //GEN_ARRAY
    const opus_int16 * a_x = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_x, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_ARRAY
    const opus_int16 * a_y = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_y, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_ARRAY
    opus_int32 * a_mid_res_amp_Q0 = (opus_int32 *) malloc(sizeof(int) * 0);
    memcpy(a_mid_res_amp_Q0, futag_pos, 0 * sizeof(int));
    futag_pos += 0 * sizeof(int);
    
    //GEN_BUILTIN
    int b_length;
    memcpy(&b_length, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_smooth_coef_Q16;
    memcpy(&b_smooth_coef_Q16, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    silk_stereo_find_predictor(p_b__ratio_Q14 ,a_x ,a_y ,a_mid_res_amp_Q0 ,b_length ,b_smooth_coef_Q16 );
    //FREE
    if (a_x) {
        free( a_x);
        a_x = NULL;
    }
    if (a_y) {
        free( a_y);
        a_y = NULL;
    }
    if (a_mid_res_amp_Q0) {
        free( a_mid_res_amp_Q0);
        a_mid_res_amp_Q0 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/stereo_find_predictor.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/stereo_find_predictor.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/stereo_find_predictor.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_stereo_find_predictor/silk_stereo_find_predictor1/silk_stereo_find_predictor1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_stereo_find_predictor/silk_stereo_find_predictor1/silk_stereo_find_predictor1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_stereo_find_predictor/silk_stereo_find_predictor1/silk_stereo_find_predictor1.c:43:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_x, futag_pos, 0 * sizeof(short));
           ^~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_stereo_find_predictor/silk_stereo_find_predictor1/silk_stereo_find_predictor1.c:48:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_y, futag_pos, 0 * sizeof(short));
           ^~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_stereo_find_predictor/silk_stereo_find_predictor1/silk_stereo_find_predictor1.c:70:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_x);
              ^~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_stereo_find_predictor/silk_stereo_find_predictor1/silk_stereo_find_predictor1.c:74:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_y);
              ^~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
4 warnings generated.

 */
