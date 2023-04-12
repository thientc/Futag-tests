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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 2 + 0 + sizeof(opus_int8) + sizeof(opus_int32) + sizeof(opus_int32) + sizeof(int) + sizeof(opus_int32) + sizeof(opus_int32) + sizeof(opus_int8) + sizeof(opus_int32) + sizeof(int)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 2 + 0 + sizeof(opus_int8) + sizeof(opus_int32) + sizeof(opus_int32) + sizeof(int) + sizeof(opus_int32) + sizeof(opus_int32) + sizeof(opus_int8) + sizeof(opus_int32) + sizeof(int) )));
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
    //GEN_BUILTIN
    opus_int8 b__ind;
    memcpy(&b__ind, futag_pos, sizeof(opus_int8));
    futag_pos += sizeof(opus_int8);
    //GEN_POINTER
    opus_int8 * p_b__ind = & b__ind;
    
    //GEN_BUILTIN
    opus_int32 b__res_nrg_Q15;
    memcpy(&b__res_nrg_Q15, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_POINTER
    opus_int32 * p_b__res_nrg_Q15 = & b__res_nrg_Q15;
    
    //GEN_BUILTIN
    opus_int32 b__rate_dist_Q8;
    memcpy(&b__rate_dist_Q8, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_POINTER
    opus_int32 * p_b__rate_dist_Q8 = & b__rate_dist_Q8;
    
    //GEN_BUILTIN
    int b__gain_Q7;
    memcpy(&b__gain_Q7, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__gain_Q7 = & b__gain_Q7;
    
    //GEN_BUILTIN
    opus_int32 b__XX_Q17;
    memcpy(&b__XX_Q17, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__XX_Q17 = b__XX_Q17;
    //GEN_POINTER
    const opus_int32 * p_q_b__XX_Q17 = & q_b__XX_Q17;
    
    //GEN_BUILTIN
    opus_int32 b__xX_Q17;
    memcpy(&b__xX_Q17, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__xX_Q17 = b__xX_Q17;
    //GEN_POINTER
    const opus_int32 * p_q_b__xX_Q17 = & q_b__xX_Q17;
    
    //GEN_BUILTIN
    opus_int8 b__cb_Q7;
    memcpy(&b__cb_Q7, futag_pos, sizeof(opus_int8));
    futag_pos += sizeof(opus_int8);
    //GEN_QUALIFIED
    const opus_int8 q_b__cb_Q7 = b__cb_Q7;
    //GEN_POINTER
    const opus_int8 * p_q_b__cb_Q7 = & q_b__cb_Q7;
    
    //GEN_CSTRING
    unsigned char * rstr_cb_gain_Q7 = (unsigned char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(rstr_cb_gain_Q7, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_cb_gain_Q7, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    const opus_uint8 * str_cb_gain_Q7 = rstr_cb_gain_Q7;
    
    //GEN_CSTRING
    unsigned char * rstr_cl_Q5 = (unsigned char *) malloc((dyn_cstring_size[1] + 1)* sizeof(char));
    memset(rstr_cl_Q5, 0, dyn_cstring_size[1] + 1);
    memcpy(rstr_cl_Q5, futag_pos, dyn_cstring_size[1]);
    futag_pos += dyn_cstring_size[1];
    const opus_uint8 * str_cl_Q5 = rstr_cl_Q5;
    
    //GEN_SIZE
    const int sz__subfr_len = (const int) dyn_cstring_size[1];
    
    //GEN_BUILTIN
    opus_int32 b__max_gain_Q7;
    memcpy(&b__max_gain_Q7, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__max_gain_Q7 = b__max_gain_Q7;
    
    //GEN_BUILTIN
    int b__L;
    memcpy(&b__L, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__L = b__L;
    
    //FUNCTION_CALL
    silk_VQ_WMat_EC_c(p_b__ind ,p_b__res_nrg_Q15 ,p_b__rate_dist_Q8 ,p_b__gain_Q7 ,p_q_b__XX_Q17 ,p_q_b__xX_Q17 ,p_q_b__cb_Q7 ,str_cb_gain_Q7 ,str_cl_Q5 ,sz__subfr_len ,q_b__max_gain_Q7 ,q_b__L );
    //FREE
    if (rstr_cb_gain_Q7) {
        free(rstr_cb_gain_Q7);
        rstr_cb_gain_Q7 = NULL;
    }
    if (rstr_cl_Q5) {
        free(rstr_cl_Q5);
        rstr_cl_Q5 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/VQ_WMat_EC.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/VQ_WMat_EC.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/VQ_WMat_EC.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_VQ_WMat_EC_c/silk_VQ_WMat_EC_c1/silk_VQ_WMat_EC_c1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_VQ_WMat_EC_c/silk_VQ_WMat_EC_c1/silk_VQ_WMat_EC_c1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
