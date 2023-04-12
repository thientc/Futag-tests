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
#include "main.h"
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
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 1 + 0 + 0 * sizeof(int) + 0 * sizeof(short) + 0 * sizeof(short) + sizeof(int) + sizeof(int)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 1 + 0 + 0 * sizeof(int) + 0 * sizeof(short) + 0 * sizeof(short) + sizeof(int) + sizeof(int) )));
    //generate random array of dynamic string sizes
    size_t dyn_cstring_size[1];
    dyn_cstring_size[0] = dyn_cstring_buffer;
    //end of generation random array of dynamic string sizes
    uint8_t * futag_pos = Fuzz_Data;
    //GEN_ARRAY
    opus_int32 * a_err_Q24 = (opus_int32 *) malloc(sizeof(int) * 0);
    memcpy(a_err_Q24, futag_pos, 0 * sizeof(int));
    futag_pos += 0 * sizeof(int);
    
    //GEN_ARRAY
    const opus_int16 * a_in_Q15 = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_in_Q15, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_CSTRING
    unsigned char * rstr_pCB_Q8 = (unsigned char *) malloc((dyn_cstring_size[0] + 1)* sizeof(char));
    memset(rstr_pCB_Q8, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_pCB_Q8, futag_pos, dyn_cstring_size[0]);
    futag_pos += dyn_cstring_size[0];
    const opus_uint8 * str_pCB_Q8 = rstr_pCB_Q8;
    
    //GEN_ARRAY
    const opus_int16 * a_pWght_Q9 = (const opus_int16 *) malloc(sizeof(short) * 0);
    memcpy(a_pWght_Q9, futag_pos, 0 * sizeof(short));
    futag_pos += 0 * sizeof(short);
    
    //GEN_BUILTIN
    int b__K;
    memcpy(&b__K, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__K = b__K;
    
    //GEN_BUILTIN
    int b__LPC_order;
    memcpy(&b__LPC_order, futag_pos, sizeof(int));
    futag_pos += sizeof(int);
    //GEN_QUALIFIED
    const int q_b__LPC_order = b__LPC_order;
    
    //FUNCTION_CALL
    silk_NLSF_VQ(a_err_Q24 ,a_in_Q15 ,str_pCB_Q8 ,a_pWght_Q9 ,q_b__K ,q_b__LPC_order );
    //FREE
    if (a_err_Q24) {
        free( a_err_Q24);
        a_err_Q24 = NULL;
    }
    if (a_in_Q15) {
        free( a_in_Q15);
        a_in_Q15 = NULL;
    }
    if (rstr_pCB_Q8) {
        free(rstr_pCB_Q8);
        rstr_pCB_Q8 = NULL;
    }
    if (a_pWght_Q9) {
        free( a_pWght_Q9);
        a_pWght_Q9 = NULL;
    }
    return 0;
}
// Compile database: 
/*
command: cc -c -DHAVE_CONFIG_H -I. -I/home/futag/Futag-tests/libopus/opus-1.3.1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/include -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed -g -O0 -fsanitize=address -g -O0 -fsanitize=address -fPIC -DPIC -o silk/.libs/NLSF_VQ.o /home/futag/Futag-tests/libopus/opus-1.3.1/silk/NLSF_VQ.c
location: /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build
file: /home/futag/Futag-tests/libopus/opus-1.3.1/silk/NLSF_VQ.c
*/

// Compile command:
/* 
/home/futag/Futag-tests/futag-llvm/bin/clang -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/include/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/celt/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/float/ -I/home/futag/Futag-tests/libopus/opus-1.3.1/silk/fixed/ -DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/ /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_NLSF_VQ/silk_NLSF_VQ1/silk_NLSF_VQ1.c -o /home/futag/Futag-tests/libopus/opus-1.3.1/futag-fuzz-drivers/succeeded/silk_NLSF_VQ/silk_NLSF_VQ1/silk_NLSF_VQ1.out -Wl,--start-group /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/.libs/libopus.a /home/futag/Futag-tests/libopus/opus-1.3.1/.futag-install/lib/libopus.a -Wl,--end-group 
 */

// Error log:
/* 
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_VQ/silk_NLSF_VQ1/silk_NLSF_VQ1.c:42:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_in_Q15, futag_pos, 0 * sizeof(short));
           ^~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_VQ/silk_NLSF_VQ1/silk_NLSF_VQ1.c:54:12: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
    memcpy(a_pWght_Q9, futag_pos, 0 * sizeof(short));
           ^~~~~~~~~~
/usr/include/string.h:43:39: note: passing argument to parameter '__dest' here
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                                      ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_VQ/silk_NLSF_VQ1/silk_NLSF_VQ1.c:79:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_in_Q15);
              ^~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-fuzz-drivers/silk_NLSF_VQ/silk_NLSF_VQ1/silk_NLSF_VQ1.c:87:15: warning: passing 'const opus_int16 *' (aka 'const short *') to parameter of type 'void *' discards qualifiers [-Wincompatible-pointer-types-discards-qualifiers]
        free( a_pWght_Q9);
              ^~~~~~~~~~
/usr/include/stdlib.h:555:25: note: passing argument to parameter '__ptr' here
extern void free (void *__ptr) __THROW;
                        ^
4 warnings generated.

 */
