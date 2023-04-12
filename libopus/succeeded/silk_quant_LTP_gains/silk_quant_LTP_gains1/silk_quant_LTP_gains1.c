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

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + 20 * sizeof(short) + 4 * sizeof(signed char) + sizeof(opus_int8) + sizeof(opus_int32) + sizeof(int) + 100 * sizeof(int) + 20 * sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    opus_int16 * a_B_Q14 = (opus_int16 *) malloc(sizeof(short) * 20);
    memcpy(a_B_Q14, futag_pos, 20 * sizeof(short));
    futag_pos += 20 * sizeof(short);
    
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
    int b__pred_gain_dB_Q7;
    memcpy(&b__pred_gain_dB_Q7, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__pred_gain_dB_Q7 = & b__pred_gain_dB_Q7;
    
    //GEN_ARRAY
    const opus_int32 * a_XX_Q17 = (const opus_int32 *) malloc(sizeof(int) * 100);
    memcpy(a_XX_Q17, futag_pos, 100 * sizeof(int));
    futag_pos += 100 * sizeof(int);
    
    //GEN_ARRAY
    const opus_int32 * a_xX_Q17 = (const opus_int32 *) malloc(sizeof(int) * 20);
    memcpy(a_xX_Q17, futag_pos, 20 * sizeof(int));
    futag_pos += 20 * sizeof(int);
    
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
    silk_quant_LTP_gains(a_B_Q14 ,a_cbk_index ,p_b__periodicity_index ,p_b__sum_log_gain_Q7 ,p_b__pred_gain_dB_Q7 ,a_XX_Q17 ,a_xX_Q17 ,q_b__subfr_len ,q_b__nb_subfr ,b_arch );
    //FREE
    if (a_B_Q14) {
        free( a_B_Q14);
        a_B_Q14 = NULL;
    }
    if (a_cbk_index) {
        free( a_cbk_index);
        a_cbk_index = NULL;
    }
    if (a_XX_Q17) {
        free( a_XX_Q17);
        a_XX_Q17 = NULL;
    }
    if (a_xX_Q17) {
        free( a_xX_Q17);
        a_xX_Q17 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/quant_LTP_gains.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/quant_LTP_gains.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/quant_LTP_gains.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_quant_LTP_gains/silk_quant_LTP_gains1/silk_quant_LTP_gains1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_quant_LTP_gains/silk_quant_LTP_gains1/silk_quant_LTP_gains1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains/silk_quant_LTP_gains1/silk_quant_LTP_gains1.c:64:12: warning: passing 'const opus_int32 *' (aka 'const int *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_XX_Q17, futag_pos, 100 * sizeof(int));
           ^~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains/silk_quant_LTP_gains1/silk_quant_LTP_gains1.c:69:12: warning: passing 'const opus_int32 *' (aka 'const int *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_xX_Q17, futag_pos, 20 * sizeof(int));
           ^~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains/silk_quant_LTP_gains1/silk_quant_LTP_gains1.c:103:15: warning: passing 'const opus_int32 *' (aka 'const int *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_XX_Q17);
              ^~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_quant_LTP_gains/silk_quant_LTP_gains1/silk_quant_LTP_gains1.c:107:15: warning: passing 'const opus_int32 *' (aka 'const int *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_xX_Q17);
              ^~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
4 warnings generated.

 */
