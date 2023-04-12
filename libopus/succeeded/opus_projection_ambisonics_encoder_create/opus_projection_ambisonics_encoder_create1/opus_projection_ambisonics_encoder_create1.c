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
#include "mathops.h"
#include "opus_private.h"
#include "opus_projection.h"
#include "stack_alloc.h"
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

extern "C" int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 0 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_BUILTIN
    opus_int32 b_Fs;
    memcpy(&b_Fs, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    
    //GEN_BUILTIN
    int b_channels;
    memcpy(&b_channels, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_mapping_family;
    memcpy(&b_mapping_family, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b__streams;
    memcpy(&b__streams, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__streams = & b__streams;
    
    //GEN_BUILTIN
    int b__coupled_streams;
    memcpy(&b__coupled_streams, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__coupled_streams = & b__coupled_streams;
    
    //GEN_BUILTIN
    int b_application;
    memcpy(&b_application, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b__error;
    memcpy(&b__error, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__error = & b__error;
    
    //FUNCTION_CALL
    opus_projection_ambisonics_encoder_create(b_Fs ,b_channels ,b_mapping_family ,p_b__streams ,p_b__coupled_streams ,b_application ,p_b__error );
    //FREE
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -o src/opus_encoder.o /home/futag/Futag-tests/libopus/opus-1.3.1/src/opus_encoder.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/src/opus_encoder.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang++ -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_projection_ambisonics_encoder_create/opus_projection_ambisonics_encoder_create1/opus_projection_ambisonics_encoder_create1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_projection_ambisonics_encoder_create/opus_projection_ambisonics_encoder_create1/opus_projection_ambisonics_encoder_create1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
clang-14: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_projection_ambisonics_encoder_create/opus_projection_ambisonics_encoder_create1/opus_projection_ambisonics_encoder_create1.c:71:5: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
    opus_projection_ambisonics_encoder_create(b_Fs ,b_channels ,b_mapping_family ,p_b__streams ,p_b__coupled_streams ,b_application ,p_b__error );
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning generated.

 */
