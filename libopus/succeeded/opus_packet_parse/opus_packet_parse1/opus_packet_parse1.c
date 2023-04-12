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
#include "opus.h"
#include "opus_private.h"
#include "mathops.h"
#include "opus_projection.h"
#include "mapping_matrix.h"
#include "stack_alloc.h"
#include <stdarg.h>
#include "celt.h"
#include "modes.h"
#include "API.h"
#include "float_cast.h"
#include "os_support.h"
#include "structs.h"
#include "opus_multistream.h"
#include "mdct.h"
#include "bands.h"
#include "quant_bands.h"
#include "pitch.h"
#include "analysis.h"
#include "tuning_parameters.h"
#include "float/structs_FLP.h"

int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 3 + 0 + sizeof(opus_int32) + 48 * sizeof(short) + sizeof(int)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 3 + 0 + sizeof(opus_int32) + 48 * sizeof(short) + sizeof(int) )));
    //generate random array of dynamic string sizes
    size_t dyn_cstring_size[3];
    srand(time(NULL));
    if(dyn_cstring_buffer == 0) dyn_cstring_size[0] = dyn_cstring_buffer; 
    else dyn_cstring_size[0] = rand() % dyn_cstring_buffer; 
    size_t remain = dyn_cstring_size[0];
    for(size_t i = 1; i< 3 - 1; i++){
        if(dyn_cstring_buffer - remain == 0) dyn_cstring_size[i] = dyn_cstring_buffer - remain;
        else dyn_cstring_size[i] = rand() % (dyn_cstring_buffer - remain);
        remain += dyn_cstring_size[i];
    }
    dyn_cstring_size[3 - 1] = dyn_cstring_buffer - remain;
    //end of generation random array of dynamic string sizes
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_CSTRING
    unsigned char * rstr_data = (unsigned char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(rstr_data, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_data, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    const unsigned char * str_data = rstr_data;
    
    //GEN_BUILTIN
    opus_int32 b_len;
    memcpy(&b_len, futag_pos, sizeof(opus_int32));
    futag_pos += sizeof(opus_int32);
    
    //GEN_CSTRING
    char * str_out_toc = (char *) malloc((dyn_cstring_size[1] + 1)* sizeof(char));
    memset(str_out_toc, 0, dyn_cstring_size[1] + 1);
    memcpy(str_out_toc, futag_pos, dyn_cstring_size[1]);
    futag_pos += dyn_cstring_size[1];
    
    //GEN_CSTRING
    char * rstr__frames = (char *) malloc((dyn_cstring_size[2] + 1)* sizeof(char));
    memset(rstr__frames, 0, dyn_cstring_size[2] + 1);
    memcpy(rstr__frames, futag_pos, dyn_cstring_size[2]);
    futag_pos += dyn_cstring_size[2];
    const unsigned char * str__frames = rstr__frames;
    //GEN_POINTER
    const unsigned char ** p_str__frames = & str__frames;
    
    //GEN_ARRAY
    opus_int16 * a_size = (opus_int16 *) malloc(sizeof(short) * 48);
    memcpy(a_size, futag_pos, 48 * sizeof(short));
    futag_pos += 48 * sizeof(short);
    
    //GEN_BUILTIN
    int b__payload_offset;
    memcpy(&b__payload_offset, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_POINTER
    int * p_b__payload_offset = & b__payload_offset;
    
    //FUNCTION_CALL
    opus_packet_parse(str_data ,b_len ,str_out_toc ,p_str__frames ,a_size ,p_b__payload_offset );
    //FREE
    if (rstr_data) {
        free(rstr_data);
        rstr_data = NULL;
    }
    if (str_out_toc) {
        free(str_out_toc);
        str_out_toc = NULL;
    }
    if (rstr__frames) {
        free(rstr__frames);
        rstr__frames = NULL;
    }
    if (a_size) {
        free( a_size);
        a_size = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o src/.libs/opus.o /home/futag/Futag-tests/libopus/opus-1.3.1/src/opus.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/src/opus.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_packet_parse/opus_packet_parse1/opus_packet_parse1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/opus_packet_parse/opus_packet_parse1/opus_packet_parse1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_packet_parse/opus_packet_parse1/opus_packet_parse1.c:73:27: warning: initializing 'const unsigned char *' with an expression of type 'char *' converts between pointers to integer types where one is of the unique plain 'char' type and the other is not [-Wpointer-sign]
    const unsigned char * str__frames = rstr__frames;
                          ^             ~~~~~~~~~~~~
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/opus_packet_parse/opus_packet_parse1/opus_packet_parse1.c:90:40: warning: passing 'char *' to parameter of type 'unsigned char *' converts between pointers to integer types where one is of the unique plain 'char' type and the other is not [-Wpointer-sign]
    opus_packet_parse(str_data ,b_len ,str_out_toc ,p_str__frames ,a_size ,p_b__payload_offset );
                                       ^~~~~~~~~~~
/home/futag/Futag-tests/libopus/opus-1.3.1/include/opus.h:530:19: note: passing argument to parameter 'out_toc' here
   unsigned char *out_toc,
                  ^
2 warnings generated.

 */
