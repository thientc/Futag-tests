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
#include "opus_projection.h"
#include "mapping_matrix.h"
#include <stdarg.h>
#include "celt.h"
#include "opus.h"
#include "modes.h"
#include "API.h"
#include "structs.h"

extern "C" int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 2 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(opus_int32) + sizeof(opus_int16) + sizeof(int) + sizeof(int)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 2 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(opus_int32) + sizeof(opus_int16) + sizeof(int) + sizeof(int) )));
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
    opus_int32 b_1_Fs;
    memcpy(&b_1_Fs, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    //GEN_BUILTIN
    int b_1_channels;
    memcpy(&b_1_channels, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_BUILTIN
    int b_1_streams;
    memcpy(&b_1_streams, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_BUILTIN
    int b_1_coupled_streams;
    memcpy(&b_1_coupled_streams, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_CSTRING
    unsigned char * rstr_1_mapping0 = (unsigned char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(rstr_1_mapping0, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_1_mapping0, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    const unsigned char * str_1_mapping0 = rstr_1_mapping0;
    //GEN_SIZE
    int * sz__1_error = (int *) dyn_cstring_size[0];
    //GEN_VAR_FUNCTION
    OpusMSDecoder * s__st = opus_multistream_decoder_create(b_1_Fs,b_1_channels,b_1_streams,b_1_coupled_streams,str_1_mapping0,sz__1_error);
    //GEN_CSTRING
    unsigned char * rstr_data = (unsigned char *) malloc((dyn_cstring_size[1] + 1)* sizeof(char));
    memset(rstr_data, 0, dyn_cstring_size[1] + 1);
    memcpy(rstr_data, futag_pos, dyn_cstring_size[1]);
    futag_pos += dyn_cstring_size[1];
    const unsigned char * str_data = rstr_data;
    
    //GEN_BUILTIN
    opus_int32 b_len;
    memcpy(&b_len, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    
    //GEN_BUILTIN
    opus_int16 b__pcm;
    memcpy(&b__pcm, futag_pos, sizeof(opus_int16));
    futag_pos += sizeof(opus_int16);
    //GEN_POINTER
    opus_int16 * p_b__pcm = & b__pcm;
    
    //GEN_BUILTIN
    int b_frame_size;
    memcpy(&b_frame_size, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_BUILTIN
    int b_decode_fec;
    memcpy(&b_decode_fec, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //FUNCTION_CALL
    opus_multistream_decode(s__st ,str_data ,b_len ,p_b__pcm ,b_frame_size ,b_decode_fec );
    //FREE
    if (rstr_1_mapping0) {
        free(rstr_1_mapping0);
        rstr_1_mapping0 = NULL;
    }
    if (rstr_data) {
        free(rstr_data);
        rstr_data = NULL;
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
/home/futag/Futag-tests/futag-llvm/bin/clang++ -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_multistream_decode/opus_multistream_decode1/opus_multistream_decode1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_multistream_decode/opus_multistream_decode1/opus_multistream_decode1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
clang-14: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_multistream_decode/opus_multistream_decode1/opus_multistream_decode1.c:100:5: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
    opus_multistream_decode(s__st ,str_data ,b_len ,p_b__pcm ,b_frame_size ,b_decode_fec );
    ^~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning generated.

 */
