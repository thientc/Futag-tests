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
#include "cpu_support.h"
#include "os_support.h"
#include "mdct.h"
#include "celt.h"
#include "pitch.h"
#include "bands.h"
#include "quant_bands.h"
#include "float_cast.h"
#include "celt_lpc.h"
#include "vq.h"
#include "mathops.h"
#include "opus_private.h"
#include "opus_projection.h"
#include "mapping_matrix.h"
#include "stack_alloc.h"
#include <stdarg.h>
#include "opus.h"
#include "modes.h"
#include "API.h"
#include "structs.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_val16) + sizeof(celt_sig) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(opus_val16) + sizeof(celt_sig) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_val16 b__pcmp;
    memcpy(&b__pcmp, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__pcmp = b__pcmp;
    //GEN_POINTER
    const opus_val16 *__restrict p_q_b__pcmp = & q_b__pcmp;
    
    //GEN_BUILTIN
    celt_sig b__inp;
    memcpy(&b__inp, futag_pos, sizeof(celt_sig));
    futag_pos += sizeof(celt_sig);
    //GEN_POINTER
    celt_sig *__restrict p_b__inp = & b__inp;
    
    //GEN_BUILTIN
    int b_N;
    memcpy(&b_N, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_CC;
    memcpy(&b_CC, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_upsample;
    memcpy(&b_upsample, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    opus_val16 b__coef;
    memcpy(&b__coef, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__coef = b__coef;
    //GEN_POINTER
    const opus_val16 * p_q_b__coef = & q_b__coef;
    
    //GEN_BUILTIN
    celt_sig b__mem;
    memcpy(&b__mem, futag_pos, sizeof(celt_sig));
    futag_pos += sizeof(celt_sig);
    //GEN_POINTER
    celt_sig * p_b__mem = & b__mem;
    
    //GEN_BUILTIN
    int b_clip;
    memcpy(&b_clip, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    celt_preemphasis(p_q_b__pcmp ,p_b__inp ,b_N ,b_CC ,b_upsample ,p_q_b__coef ,p_b__mem ,b_clip );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o celt/.libs/celt_encoder.o /home/futag/Futag-tests/libopus/opus-1.3.1/celt/celt_encoder.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/celt/celt_encoder.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/celt_preemphasis/celt_preemphasis1/celt_preemphasis1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/celt_preemphasis/celt_preemphasis1/celt_preemphasis1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
