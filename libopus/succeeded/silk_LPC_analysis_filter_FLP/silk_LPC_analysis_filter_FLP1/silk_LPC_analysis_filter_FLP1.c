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

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + 0 * sizeof(float) + 0 * sizeof(float) + 0 * sizeof(float) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    float * a_r_LPC = (float *) malloc(sizeof(float) * 0);
    memcpy(a_r_LPC, futag_pos, 0 * sizeof(float));
    futag_pos += 0 * sizeof(float);
    
    //GEN_ARRAY
    const float * a_PredCoef = (const float *) malloc(sizeof(float) * 0);
    memcpy(a_PredCoef, futag_pos, 0 * sizeof(float));
    futag_pos += 0 * sizeof(float);
    
    //GEN_ARRAY
    const float * a_s = (const float *) malloc(sizeof(float) * 0);
    memcpy(a_s, futag_pos, 0 * sizeof(float));
    futag_pos += 0 * sizeof(float);
    
    //GEN_BUILTIN
    int b__length;
    memcpy(&b__length, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__length = b__length;
    
    //GEN_BUILTIN
    int b__Order;
    memcpy(&b__Order, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__Order = b__Order;
    
    //FUNCTION_CALL
    silk_LPC_analysis_filter_FLP(a_r_LPC ,a_PredCoef ,a_s ,q_b__length ,q_b__Order );
    //FREE
    if (a_r_LPC) {
        free( a_r_LPC);
        a_r_LPC = NULL;
    }
    if (a_PredCoef) {
        free( a_PredCoef);
        a_PredCoef = NULL;
    }
    if (a_s) {
        free( a_s);
        a_s = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/float/.libs/LPC_analysis_filter_FLP.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/LPC_analysis_filter_FLP.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/LPC_analysis_filter_FLP.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.c:12:
/home/futag/Futag-tests/libopus/opus-1.3.1/celt/mathops.h:41:9: warning: 'PI' macro redefined [-Wmacro-redefined]
#define PI 3.141592653f
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/SigProc_FLP.h:143:9: note: previous definition is here
#define PI              (3.1415926536f)
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.c:37:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_PredCoef, futag_pos, 0 * sizeof(float));
           ^~~~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.c:42:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_s, futag_pos, 0 * sizeof(float));
           ^~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.c:67:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_PredCoef);
              ^~~~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_LPC_analysis_filter_FLP/silk_LPC_analysis_filter_FLP1/silk_LPC_analysis_filter_FLP1.c:71:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_s);
              ^~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
5 warnings generated.

 */
