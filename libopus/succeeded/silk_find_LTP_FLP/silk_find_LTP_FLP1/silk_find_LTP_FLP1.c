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
#include "tuning_parameters.h"
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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + 100 * sizeof(float) + 20 * sizeof(float) + 0 * sizeof(float) + 4 * sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    float * a_XX = (float *) malloc(sizeof(float) * 100);
    memcpy(a_XX, futag_pos, 100 * sizeof(float));
    futag_pos += 100 * sizeof(float);
    
    //GEN_ARRAY
    float * a_xX = (float *) malloc(sizeof(float) * 20);
    memcpy(a_xX, futag_pos, 20 * sizeof(float));
    futag_pos += 20 * sizeof(float);
    
    //GEN_ARRAY
    const float * a_r_ptr = (const float *) malloc(sizeof(float) * 0);
    memcpy(a_r_ptr, futag_pos, 0 * sizeof(float));
    futag_pos += 0 * sizeof(float);
    
    //GEN_ARRAY
    const int * a_lag = (const int *) malloc(sizeof(int) * 4);
    memcpy(a_lag, futag_pos, 4 * sizeof(int));
    futag_pos += 4 * sizeof(int);
    
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
    
    //FUNCTION_CALL
    silk_find_LTP_FLP(a_XX ,a_xX ,a_r_ptr ,a_lag ,q_b__subfr_length ,q_b__nb_subfr );
    //FREE
    if (a_XX) {
        free( a_XX);
        a_XX = NULL;
    }
    if (a_xX) {
        free( a_xX);
        a_xX = NULL;
    }
    if (a_r_ptr) {
        free( a_r_ptr);
        a_r_ptr = NULL;
    }
    if (a_lag) {
        free( a_lag);
        a_lag = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/float/.libs/find_LTP_FLP.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/find_LTP_FLP.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/find_LTP_FLP.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.c:13:
/home/futag/Futag-tests/libopus/opus-1.3.1/celt/mathops.h:41:9: warning: 'PI' macro redefined [-Wmacro-redefined]
#define PI 3.141592653f
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/SigProc_FLP.h:143:9: note: previous definition is here
#define PI              (3.1415926536f)
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.c:47:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_r_ptr, futag_pos, 0 * sizeof(float));
           ^~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.c:52:12: warning: passing 'const int *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_lag, futag_pos, 4 * sizeof(int));
           ^~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.c:81:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_r_ptr);
              ^~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_find_LTP_FLP/silk_find_LTP_FLP1/silk_find_LTP_FLP1.c:85:15: warning: passing 'const int *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_lag);
              ^~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
5 warnings generated.

 */
