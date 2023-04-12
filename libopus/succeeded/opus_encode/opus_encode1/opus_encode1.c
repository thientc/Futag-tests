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
#include <stdarg.h>
#include "celt.h"
#include "modes.h"
#include "API.h"
#include "stack_alloc.h"
#include "float_cast.h"
#include "opus.h"
#include "pitch.h"
#include "opus_private.h"
#include "os_support.h"
#include "analysis.h"
#include "mathops.h"
#include "tuning_parameters.h"
#include "float/structs_FLP.h"
#include "opus_projection.h"
#include "mapping_matrix.h"
#include "structs.h"
#include "opus_multistream.h"
#include "mdct.h"
#include "bands.h"
#include "quant_bands.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 1 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(opus_int16) + sizeof(int) + sizeof(opus_int32)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 1 + 0 + sizeof(opus_int32) + sizeof(int) + sizeof(int) + sizeof(int) + sizeof(opus_int16) + sizeof(int) + sizeof(opus_int32) )));
    //generate random array of dynamic string sizes
    size_t dyn_cstring_size[1];
    dyn_cstring_size[0] = dyn_cstring_buffer;
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
    int b_1_application;
    memcpy(&b_1_application, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_BUILTIN
    int b__1_error;
    memcpy(&b__1_error, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__1_error = & b__1_error;
    //GEN_VAR_FUNCTION
    OpusEncoder * s__st = opus_encoder_create(b_1_Fs,b_1_channels,b_1_application,p_b__1_error);
    //GEN_BUILTIN
    opus_int16 b__pcm;
    memcpy(&b__pcm, futag_pos, sizeof(opus_int16));
    futag_pos += sizeof(opus_int16);
    //GEN_QUALIFIED
    const opus_int16 q_b__pcm = b__pcm;
    //GEN_POINTER
    const opus_int16 * p_q_b__pcm = & q_b__pcm;
    
    //GEN_BUILTIN
    int b_analysis_frame_size;
    memcpy(&b_analysis_frame_size, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    
    //GEN_CSTRING
    char * str_data = (char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(str_data, 0, dyn_cstring_size[0] + 1);
    memcpy(str_data, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    
    //GEN_BUILTIN
    opus_int32 b_max_data_bytes;
    memcpy(&b_max_data_bytes, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    
    //FUNCTION_CALL
    opus_encode(s__st ,p_q_b__pcm ,b_analysis_frame_size ,str_data ,b_max_data_bytes );
    //FREE
    if (str_data) {
        free(str_data);
        str_data = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o src/.libs/opus_encoder.o /home/futag/Futag-tests/libopus/opus-1.3.1/src/opus_encoder.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/src/opus_encoder.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_encode/opus_encode1/opus_encode1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_encode/opus_encode1/opus_encode1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_encode/opus_encode1/opus_encode1.c:88:59: warning: passing 'char *' to parameter of type 'unsigned char *' converts between pointers to integer types where one is of the unique plain 'char' type and the other is not [-Wpointer-sign]
    opus_encode(s__st ,p_q_b__pcm ,b_analysis_frame_size ,str_data ,b_max_data_bytes );
                                                          ^~~~~~~~
/home/futag/Futag-tests/libopus/opus-1.3.1/include/opus.h:267:20: note: passing argument to parameter 'data' here
    unsigned char *data,
                   ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_encode/opus_encode1/opus_encode1.c:88:5: warning: ignoring return value of function declared with 'warn_unused_result' attribute [-Wunused-result]
    opus_encode(s__st ,p_q_b__pcm ,b_analysis_frame_size ,str_data ,b_max_data_bytes );
    ^~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2 warnings generated.

 */
