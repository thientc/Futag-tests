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
#include "macros.h"
#include "celt_lpc.h"
#include "stack_alloc.h"
#include "mathops.h"
#include "pitch.h"
#include <xmmintrin.h>
#include "opus_private.h"
#include "opus_projection.h"
#include "mapping_matrix.h"
#include <stdarg.h>
#include "celt.h"
#include "opus.h"
#include "modes.h"
#include "API.h"
#include "float_cast.h"
#include "os_support.h"
#include "structs.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_val16) + sizeof(opus_val16) + sizeof(opus_val16) + sizeof(int) + sizeof(opus_val32) + sizeof(opus_val32)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_val16 b__x;
    memcpy(&b__x, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__x = b__x;
    //GEN_POINTER
    const opus_val16 * p_q_b__x = & q_b__x;
    
    //GEN_BUILTIN
    opus_val16 b__y01;
    memcpy(&b__y01, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__y01 = b__y01;
    //GEN_POINTER
    const opus_val16 * p_q_b__y01 = & q_b__y01;
    
    //GEN_BUILTIN
    opus_val16 b__y02;
    memcpy(&b__y02, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__y02 = b__y02;
    //GEN_POINTER
    const opus_val16 * p_q_b__y02 = & q_b__y02;
    
    //GEN_BUILTIN
    int b_N;
    memcpy(&b_N, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    opus_val32 b__xy1;
    memcpy(&b__xy1, futag_pos, sizeof(opus_val32));
    futag_pos += sizeof(opus_val32);
    //GEN_POINTER
    opus_val32 * p_b__xy1 = & b__xy1;
    
    //GEN_BUILTIN
    opus_val32 b__xy2;
    memcpy(&b__xy2, futag_pos, sizeof(opus_val32));
    futag_pos += sizeof(opus_val32);
    //GEN_POINTER
    opus_val32 * p_b__xy2 = & b__xy2;
    
    //FUNCTION_CALL
    dual_inner_prod_sse(p_q_b__x ,p_q_b__y01 ,p_q_b__y02 ,b_N ,p_b__xy1 ,p_b__xy2 );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o celt/x86/.libs/pitch_sse.o /home/futag/Futag-tests/libopus/opus-1.3.1/celt/x86/pitch_sse.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/celt/x86/pitch_sse.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/dual_inner_prod_sse/dual_inner_prod_sse1/dual_inner_prod_sse1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/dual_inner_prod_sse/dual_inner_prod_sse1/dual_inner_prod_sse1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
