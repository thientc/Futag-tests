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
#include "celt_lpc.h"
#include "stack_alloc.h"
#include "mathops.h"
#include "pitch.h"
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
#include "opus_multistream.h"
#include "mdct.h"
#include "bands.h"
#include "quant_bands.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_val16) + sizeof(opus_val32) + sizeof(opus_val16) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int)) return 0;
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
    opus_val32 b__ac;
    memcpy(&b__ac, futag_pos, sizeof(opus_val32));
    futag_pos += sizeof(opus_val32);
    //GEN_POINTER
    opus_val32 * p_b__ac = & b__ac;
    
    //GEN_BUILTIN
    opus_val16 b__window;
    memcpy(&b__window, futag_pos, sizeof(opus_val16));
    futag_pos += sizeof(opus_val16);
    //GEN_QUALIFIED
    const opus_val16 q_b__window = b__window;
    //GEN_POINTER
    const opus_val16 * p_q_b__window = & q_b__window;
    
    //GEN_BUILTIN
    int b_overlap;
    memcpy(&b_overlap, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_lag;
    memcpy(&b_lag, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_n;
    memcpy(&b_n, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_arch;
    memcpy(&b_arch, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    _celt_autocorr(p_q_b__x ,p_b__ac ,p_q_b__window ,b_overlap ,b_lag ,b_n ,b_arch );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o celt/.libs/celt_lpc.o /home/futag/Futag-tests/libopus/opus-1.3.1/celt/celt_lpc.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/celt/celt_lpc.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/_celt_autocorr/_celt_autocorr1/_celt_autocorr1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/_celt_autocorr/_celt_autocorr1/_celt_autocorr1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 

 */
