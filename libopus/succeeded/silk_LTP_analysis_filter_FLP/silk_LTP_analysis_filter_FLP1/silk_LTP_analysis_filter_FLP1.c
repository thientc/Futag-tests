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
#include "main_FLP.h"
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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(float) + sizeof(float) + 20 * sizeof(float) + 4 * sizeof(int) + 4 * sizeof(float) + sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    float b__LTP_res;
    memcpy(&b__LTP_res, futag_pos, sizeof(float));
    futag_pos += sizeof(float);
    //GEN_POINTER
    float * p_b__LTP_res = & b__LTP_res;
    
    //GEN_BUILTIN
    float b__x;
    memcpy(&b__x, futag_pos, sizeof(float));
    futag_pos += sizeof(float);
    //GEN_QUALIFIED
    const float q_b__x = b__x;
    //GEN_POINTER
    const float * p_q_b__x = & q_b__x;
    
    //GEN_ARRAY
    const float * a_B = (const float *) malloc(sizeof(float) * 20);
    memcpy(a_B, futag_pos, 20 * sizeof(float));
    futag_pos += 20 * sizeof(float);
    
    //GEN_ARRAY
    const int * a_pitchL = (const int *) malloc(sizeof(int) * 4);
    memcpy(a_pitchL, futag_pos, 4 * sizeof(int));
    futag_pos += 4 * sizeof(int);
    
    //GEN_ARRAY
    const float * a_invGains = (const float *) malloc(sizeof(float) * 4);
    memcpy(a_invGains, futag_pos, 4 * sizeof(float));
    futag_pos += 4 * sizeof(float);
    
    //GEN_BUILTIN
    int b__subfr_length;
    memcpy(&b__subfr_length, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__subfr_length = b__subfr_length;
    
    //GEN_BUILTIN
    int b__nb_subfr;
    memcpy(&b__nb_subfr, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__nb_subfr = b__nb_subfr;
    
    //GEN_BUILTIN
    int b__pre_length;
    memcpy(&b__pre_length, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__pre_length = b__pre_length;
    
    //FUNCTION_CALL
    silk_LTP_analysis_filter_FLP(p_b__LTP_res ,p_q_b__x ,a_B ,a_pitchL ,a_invGains ,q_b__subfr_length ,q_b__nb_subfr ,q_b__pre_length );
    //FREE
    if (a_B) {
        free( a_B);
        a_B = NULL;
    }
    if (a_pitchL) {
        free( a_pitchL);
        a_pitchL = NULL;
    }
    if (a_invGains) {
        free( a_invGains);
        a_invGains = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/float/.libs/LTP_analysis_filter_FLP.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/LTP_analysis_filter_FLP.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/LTP_analysis_filter_FLP.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:12:
/home/futag/Futag-tests/libopus/opus-1.3.1/celt/mathops.h:41:9: warning: 'PI' macro redefined [-Wmacro-redefined]
#define PI 3.141592653f
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/SigProc_FLP.h:143:9: note: previous definition is here
#define PI              (3.1415926536f)
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:52:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_B, futag_pos, 20 * sizeof(float));
           ^~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:57:12: warning: passing 'const int *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_pitchL, futag_pos, 4 * sizeof(int));
           ^~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:62:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_invGains, futag_pos, 4 * sizeof(float));
           ^~~~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:90:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_B);
              ^~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:94:15: warning: passing 'const int *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_pitchL);
              ^~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LTP_analysis_filter_FLP/silk_LTP_analysis_filter_FLP1/silk_LTP_analysis_filter_FLP1.c:98:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_invGains);
              ^~~~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
7 warnings generated.

 */
