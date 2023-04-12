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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + 20 * sizeof(float) + 4 * sizeof(signed char) + sizeof(opus_int8) + sizeof(opus_int32) + sizeof(float) + 100 * sizeof(float) + 20 * sizeof(float) + sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    float * a_B = (float *) malloc(sizeof(float) * 20);
    memcpy(a_B, futag_pos, 20 * sizeof(float));
    futag_pos += 20 * sizeof(float);
    
    //GEN_ARRAY
    opus_int8 * a_cbk_index = (opus_int8 *) malloc(sizeof(signed char) * 4);
    memcpy(a_cbk_index, futag_pos, 4 * sizeof(signed char));
    futag_pos += 4 * sizeof(signed char);
    
    //GEN_BUILTIN
    opus_int8 b__periodicity_index;
    memcpy(&b__periodicity_index, futag_pos, sizeof(opus_int8));
    futag_pos += sizeof(opus_int8);
    //GEN_POINTER
    opus_int8 * p_b__periodicity_index = & b__periodicity_index;
    
    //GEN_BUILTIN
    opus_int32 b__sum_log_gain_Q7;
    memcpy(&b__sum_log_gain_Q7, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_POINTER
    opus_int32 * p_b__sum_log_gain_Q7 = & b__sum_log_gain_Q7;
    
    //GEN_BUILTIN
    float b__pred_gain_dB;
    memcpy(&b__pred_gain_dB, futag_pos, sizeof(float));
    futag_pos += sizeof(float);
    //GEN_POINTER
    float * p_b__pred_gain_dB = & b__pred_gain_dB;
    
    //GEN_ARRAY
    const float * a_XX = (const float *) malloc(sizeof(float) * 100);
    memcpy(a_XX, futag_pos, 100 * sizeof(float));
    futag_pos += 100 * sizeof(float);
    
    //GEN_ARRAY
    const float * a_xX = (const float *) malloc(sizeof(float) * 20);
    memcpy(a_xX, futag_pos, 20 * sizeof(float));
    futag_pos += 20 * sizeof(float);
    
    //GEN_BUILTIN
    int b__subfr_len;
    memcpy(&b__subfr_len, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__subfr_len = b__subfr_len;
    
    //GEN_BUILTIN
    int b__nb_subfr;
    memcpy(&b__nb_subfr, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__nb_subfr = b__nb_subfr;
    
    //GEN_BUILTIN
    int b_arch;
    memcpy(&b_arch, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    silk_quant_LTP_gains_FLP(a_B ,a_cbk_index ,p_b__periodicity_index ,p_b__sum_log_gain_Q7 ,p_b__pred_gain_dB ,a_XX ,a_xX ,q_b__subfr_len ,q_b__nb_subfr ,b_arch );
    //FREE
    if (a_B) {
        free( a_B);
        a_B = NULL;
    }
    if (a_cbk_index) {
        free( a_cbk_index);
        a_cbk_index = NULL;
    }
    if (a_XX) {
        free( a_XX);
        a_XX = NULL;
    }
    if (a_xX) {
        free( a_xX);
        a_xX = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/float/.libs/wrappers_FLP.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/wrappers_FLP.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/wrappers_FLP.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.c:12:
/home/futag/Futag-tests/libopus/opus-1.3.1/celt/mathops.h:41:9: warning: 'PI' macro redefined [-Wmacro-redefined]
#define PI 3.141592653f
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/SigProc_FLP.h:143:9: note: previous definition is here
#define PI              (3.1415926536f)
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.c:63:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_XX, futag_pos, 100 * sizeof(float));
           ^~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.c:68:12: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_xX, futag_pos, 20 * sizeof(float));
           ^~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.c:102:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_XX);
              ^~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains_FLP/silk_quant_LTP_gains_FLP1/silk_quant_LTP_gains_FLP1.c:106:15: warning: passing 'const float *' to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_xX);
              ^~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
5 warnings generated.

 */
