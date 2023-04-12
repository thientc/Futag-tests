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
#include <math.h>
#include "bands.h"
#include "vq.h"
#include "os_support.h"
#include "mathops.h"
#include "quant_bands.h"
#include "pitch.h"
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
#include "structs.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_val16) + sizeof(opus_val16) + sizeof(opus_val16) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_val16 b_val;
    memcpy(&b_val, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    
    //GEN_BUILTIN
    opus_val16 b__thresholds;
    memcpy(&b__thresholds, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__thresholds = b__thresholds;
    //GEN_POINTER
    const opus_val16 * p_q_b__thresholds = & q_b__thresholds;
    
    //GEN_BUILTIN
    opus_val16 b__hysteresis;
    memcpy(&b__hysteresis, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__hysteresis = b__hysteresis;
    //GEN_POINTER
    const opus_val16 * p_q_b__hysteresis = & q_b__hysteresis;
    
    //GEN_BUILTIN
    int b_N;
    memcpy(&b_N, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_prev;
    memcpy(&b_prev, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    hysteresis_decision(b_val ,p_q_b__thresholds ,p_q_b__hysteresis ,b_N ,b_prev );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o celt/.libs/bands.o /home/futag/Futag-tests/libopus/opus-1.3.1/celt/bands.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/celt/bands.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/hysteresis_decision/hysteresis_decision1/hysteresis_decision1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/hysteresis_decision/hysteresis_decision1/hysteresis_decision1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
