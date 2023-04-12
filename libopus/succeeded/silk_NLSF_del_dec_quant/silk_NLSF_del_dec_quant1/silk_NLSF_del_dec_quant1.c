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

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 2 + 0 + 0 * sizeof(signed char) + 0 * sizeof(short) + 0 * sizeof(short) + 0 * sizeof(short) + sizeof(opus_int16) + sizeof(opus_int32) + sizeof(opus_int16)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 2 + 0 + 0 * sizeof(signed char) + 0 * sizeof(short) + 0 * sizeof(short) + 0 * sizeof(short) + sizeof(opus_int16) + sizeof(opus_int32) + sizeof(opus_int16) )));
    //generate random array of dynamic string sizes
    size_t dyn_cstring_size[2];
    srand(time(NULL));
    if(dyn_cstring_buffer == 0) dyn_cstring_size[0] = dyn_cstring_buffer; 
    else dyn_cstring_size[0] = rand() % dyn_cstring_buffer; 
    size_t remain = dyn_cstring_size[0];
    for(size_t i = 1; i< 2 - 1; i++){
        if(dyn_cstring_buffer - remain == 0) dyn_cstring_size[i] = dyn_cstring_buffer - remain;
        else dyn_cstring_size[i] = rand() % (dyn_cstring_buffer - remain);
        remain += dyn_cstring_size[i];
    }
    dyn_cstring_size[2 - 1] = dyn_cstring_buffer - remain;
    //end of generation random array of dynamic string sizes
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    opus_int8 * a_indices = (opus_int8 *) malloc(sizeof(signed char) * 0);
    memcpy(a_indices, futag_pos, 0 * sizeof(signed char));
    futag_pos += 0 * sizeof(signed char);
    
    //GEN_ARRAY
    const opus_int16 * a_x_Q10 = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_x_Q10, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_ARRAY
    const opus_int16 * a_w_Q5 = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_w_Q5, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_CSTRING
    unsigned char * rstr_pred_coef_Q8 = (unsigned char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(rstr_pred_coef_Q8, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_pred_coef_Q8, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    const opus_uint8 * str_pred_coef_Q8 = rstr_pred_coef_Q8;
    
    //GEN_ARRAY
    const opus_int16 * a_ec_ix = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_ec_ix, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_CSTRING
    unsigned char * rstr_ec_rates_Q5 = (unsigned char *) malloc((dyn_cstring_size[1] + 1)* sizeof(char));
    memset(rstr_ec_rates_Q5, 0, dyn_cstring_size[1] + 1);
    memcpy(rstr_ec_rates_Q5, futag_pos, dyn_cstring_size[1]);
    futag_pos += dyn_cstring_size[1];
    const opus_uint8 * str_ec_rates_Q5 = rstr_ec_rates_Q5;
    
    //GEN_SIZE
    const int sz__quant_step_size_Q16 = (const int) dyn_cstring_size[1];
    
    //GEN_BUILTIN
    opus_int16 b__inv_quant_step_size_Q6;
    memcpy(&b__inv_quant_step_size_Q6, futag_pos, sizeof(opus_int16));
    futag_pos += sizeof(opus_int16);
    //GEN_QUALIFIED
    const opus_int16 q_b__inv_quant_step_size_Q6 = b__inv_quant_step_size_Q6;
    
    //GEN_BUILTIN
    opus_int32 b__mu_Q20;
    memcpy(&b__mu_Q20, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__mu_Q20 = b__mu_Q20;
    
    //GEN_BUILTIN
    opus_int16 b__order;
    memcpy(&b__order, futag_pos, sizeof(opus_int16));
    futag_pos += sizeof(opus_int16);
    //GEN_QUALIFIED
    const opus_int16 q_b__order = b__order;
    
    //FUNCTION_CALL
    silk_NLSF_del_dec_quant(a_indices ,a_x_Q10 ,a_w_Q5 ,str_pred_coef_Q8 ,a_ec_ix ,str_ec_rates_Q5 ,sz__quant_step_size_Q16 ,q_b__inv_quant_step_size_Q6 ,q_b__mu_Q20 ,q_b__order );
    //FREE
    if (a_indices) {
        free( a_indices);
        a_indices = NULL;
    }
    if (a_x_Q10) {
        free( a_x_Q10);
        a_x_Q10 = NULL;
    }
    if (a_w_Q5) {
        free( a_w_Q5);
        a_w_Q5 = NULL;
    }
    if (rstr_pred_coef_Q8) {
        free(rstr_pred_coef_Q8);
        rstr_pred_coef_Q8 = NULL;
    }
    if (a_ec_ix) {
        free( a_ec_ix);
        a_ec_ix = NULL;
    }
    if (rstr_ec_rates_Q5) {
        free(rstr_ec_rates_Q5);
        rstr_ec_rates_Q5 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/NLSF_del_dec_quant.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/NLSF_del_dec_quant.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/NLSF_del_dec_quant.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c:50:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_x_Q10, futag_pos, 0 * sizeof(short));
           ^~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c:55:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_w_Q5, futag_pos, 0 * sizeof(short));
           ^~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c:67:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_ec_ix, futag_pos, 0 * sizeof(short));
           ^~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c:109:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_x_Q10);
              ^~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c:113:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_w_Q5);
              ^~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_del_dec_quant/silk_NLSF_del_dec_quant1/silk_NLSF_del_dec_quant1.c:121:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_ec_ix);
              ^~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
6 warnings generated.

 */
