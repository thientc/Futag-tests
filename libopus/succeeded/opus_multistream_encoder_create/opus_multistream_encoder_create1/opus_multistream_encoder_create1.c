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
#include "opus_multistream.h"
#include "opus_private.h"
#include "stack_alloc.h"
#include "float_cast.h"
#include "os_support.h"
#include "mathops.h"
#include "mdct.h"
#include "modes.h"
#include "bands.h"
#include "quant_bands.h"
#include "pitch.h"
#include "opus_projection.h"
#include "mapping_matrix.h"
#include <stdarg.h>
#include "celt.h"
#include "opus.h"
#include "API.h"
#include "structs.h"

extern "C" int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 1 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 1 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int) )));
    //generate random array of dynamic string sizes
    size_t dyn_cstring_size[1];
    dyn_cstring_size[0] = dyn_cstring_buffer;
    //end of generation random array of dynamic string sizes
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
    int b_streams;
    memcpy(&b_streams, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_coupled_streams;
    memcpy(&b_coupled_streams, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_CSTRING
    unsigned char * rstr_mapping = (unsigned char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(rstr_mapping, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_mapping, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    const unsigned char * str_mapping = rstr_mapping;
    
    //GEN_SIZE
    int sz_application = (int) dyn_cstring_size[0];
    
    //GEN_BUILTIN
    int b__error;
    memcpy(&b__error, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__error = & b__error;
    
    //FUNCTION_CALL
    opus_multistream_encoder_create(b_Fs ,b_channels ,b_streams ,b_coupled_streams ,str_mapping ,sz_application ,p_b__error );
    //FREE
    if (rstr_mapping) {
        free(rstr_mapping);
        rstr_mapping = NULL;
    }
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
/home/futag/Futag-tests/futag-llvm/bin/clang++ -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_multistream_encoder_create/opus_multistream_encoder_create1/opus_multistream_encoder_create1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_multistream_encoder_create/opus_multistream_encoder_create1/opus_multistream_encoder_create1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
clang-14: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_multistream_encoder_create/opus_multistream_encoder_create1/opus_multistream_encoder_create1.c:76:5: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
    opus_multistream_encoder_create(b_Fs ,b_channels ,b_streams ,b_coupled_streams ,str_mapping ,sz_application ,p_b__error );
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning generated.

 */
