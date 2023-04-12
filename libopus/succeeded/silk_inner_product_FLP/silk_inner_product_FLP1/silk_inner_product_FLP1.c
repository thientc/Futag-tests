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
#include "SigProc_FLP.h"
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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(float) + sizeof(float) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    float b__data1;
    memcpy(&b__data1, futag_pos, sizeof(float));
    futag_pos += sizeof(float);
    //GEN_QUALIFIED
    const float q_b__data1 = b__data1;
    //GEN_POINTER
    const float * p_q_b__data1 = & q_b__data1;
    
    //GEN_BUILTIN
    float b__data2;
    memcpy(&b__data2, futag_pos, sizeof(float));
    futag_pos += sizeof(float);
    //GEN_QUALIFIED
    const float q_b__data2 = b__data2;
    //GEN_POINTER
    const float * p_q_b__data2 = & q_b__data2;
    
    //GEN_BUILTIN
    int b_dataSize;
    memcpy(&b_dataSize, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    silk_inner_product_FLP(p_q_b__data1 ,p_q_b__data2 ,b_dataSize );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/float/.libs/inner_product_FLP.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/inner_product_FLP.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/inner_product_FLP.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_inner_product_FLP/silk_inner_product_FLP1/silk_inner_product_FLP1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_inner_product_FLP/silk_inner_product_FLP1/silk_inner_product_FLP1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
In file included from /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_inner_product_FLP/silk_inner_product_FLP1/silk_inner_product_FLP1.c:12:
/home/futag/Futag-tests/libopus/opus-1.3.1/celt/mathops.h:41:9: warning: 'PI' macro redefined [-Wmacro-redefined]
#define PI 3.141592653f
        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/SigProc_FLP.h:143:9: note: previous definition is here
#define PI              (3.1415926536f)
        ^
1 warning generated.

 */
