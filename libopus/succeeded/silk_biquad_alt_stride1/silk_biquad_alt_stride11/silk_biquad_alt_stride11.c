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
#include "SigProc_FIX.h"
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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_int16) + sizeof(opus_int32) + sizeof(opus_int32) + sizeof(opus_int32) + sizeof(opus_int16) + sizeof(opus_int32)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_int16 b__in;
    memcpy(&b__in, futag_pos, sizeof(opus_int16));
    futag_pos += sizeof(opus_int16);
    //GEN_QUALIFIED
    const opus_int16 q_b__in = b__in;
    //GEN_POINTER
    const opus_int16 * p_q_b__in = & q_b__in;
    
    //GEN_BUILTIN
    opus_int32 b__B_Q28;
    memcpy(&b__B_Q28, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__B_Q28 = b__B_Q28;
    //GEN_POINTER
    const opus_int32 * p_q_b__B_Q28 = & q_b__B_Q28;
    
    //GEN_BUILTIN
    opus_int32 b__A_Q28;
    memcpy(&b__A_Q28, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__A_Q28 = b__A_Q28;
    //GEN_POINTER
    const opus_int32 * p_q_b__A_Q28 = & q_b__A_Q28;
    
    //GEN_BUILTIN
    opus_int32 b__S;
    memcpy(&b__S, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_POINTER
    opus_int32 * p_b__S = & b__S;
    
    //GEN_BUILTIN
    opus_int16 b__out;
    memcpy(&b__out, futag_pos, sizeof(opus_int16));
    futag_pos += sizeof(opus_int16);
    //GEN_POINTER
    opus_int16 * p_b__out = & b__out;
    
    //GEN_BUILTIN
    opus_int32 b__len;
    memcpy(&b__len, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_QUALIFIED
    const opus_int32 q_b__len = b__len;
    
    //FUNCTION_CALL
    silk_biquad_alt_stride1(p_q_b__in ,p_q_b__B_Q28 ,p_q_b__A_Q28 ,p_b__S ,p_b__out ,q_b__len );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/biquad_alt.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/biquad_alt.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/biquad_alt.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_biquad_alt_stride1/silk_biquad_alt_stride11/silk_biquad_alt_stride11.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_biquad_alt_stride1/silk_biquad_alt_stride11/silk_biquad_alt_stride11.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
