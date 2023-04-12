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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_val32) + sizeof(opus_val32) + sizeof(int) + sizeof(int) + sizeof(opus_val16) + sizeof(opus_val16) + sizeof(opus_val16)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_val32 b__y;
    memcpy(&b__y, futag_pos, sizeof(opus_val32));
    futag_pos += sizeof(opus_val32);
    //GEN_POINTER
    opus_val32 * p_b__y = & b__y;
    
    //GEN_BUILTIN
    opus_val32 b__x;
    memcpy(&b__x, futag_pos, sizeof(opus_val32));
    futag_pos += sizeof(opus_val32);
    //GEN_POINTER
    opus_val32 * p_b__x = & b__x;
    
    //GEN_BUILTIN
    int b_T;
    memcpy(&b_T, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_N;
    memcpy(&b_N, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    opus_val16 b_g10;
    memcpy(&b_g10, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    
    //GEN_BUILTIN
    opus_val16 b_g11;
    memcpy(&b_g11, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    
    //GEN_BUILTIN
    opus_val16 b_g12;
    memcpy(&b_g12, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    
    //FUNCTION_CALL
    comb_filter_const_sse(p_b__y ,p_b__x ,b_T ,b_N ,b_g10 ,b_g11 ,b_g12 );
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
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/comb_filter_const_sse/comb_filter_const_sse1/comb_filter_const_sse1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/comb_filter_const_sse/comb_filter_const_sse1/comb_filter_const_sse1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
