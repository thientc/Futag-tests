#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "config.h"
#include "strerror_override.h"
#include <assert.h>
#include <limits.h>
#include <math.h>
#include "arraylist.h"
#include "debug.h"
#include "json_object_private.h"
#include "json_util.h"
#include "linkhash.h"
#include "math_compat.h"
#include "snprintf_compat.h"
#include "strdup_compat.h"

extern "C" int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    if (Fuzz_Size < 0*sizeof(wchar_t) + 0*sizeof(char) + 3 + 0 + sizeof(int64_t) + sizeof(int64_t) + sizeof(int32_t)) return 0;
    size_t dyn_cstring_buffer = (size_t) ((Fuzz_Size + sizeof(char) - (0*sizeof(wchar_t) + 0*sizeof(char) + 3 + 0 + sizeof(int64_t) + sizeof(int64_t) + sizeof(int32_t) )));
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
    struct json_object * body = json_object_new_object();
    //GEN_CSTRING
    char * rstr_s0 = (char *) malloc(dyn_cstring_size[0] + 1);
    memset(rstr_s0, 0, dyn_cstring_size[0] + 1);
    memcpy(rstr_s0, futag_pos, dyn_cstring_size[0] );
    futag_pos += dyn_cstring_size[0];
    const char * str_s0 = rstr_s0;
    
    struct json_object * FutagRefVarOuS = json_object_new_string(str_s0 );
    //FREE
    if (rstr_s0) {
        free(rstr_s0);
        rstr_s0 = NULL;
    }
    //GEN_CSTRING
    char * rstr_s1 = (char *) malloc(dyn_cstring_size[1] + 1);
    memset(rstr_s1, 0, dyn_cstring_size[1] + 1);
    memcpy(rstr_s1, futag_pos, dyn_cstring_size[1] );
    futag_pos += dyn_cstring_size[1];
    const char * str_s1 = rstr_s1;
    
    struct json_object * FutagRefVar1U8 = json_object_new_string(str_s1 );
    //FREE
    if (rstr_s1) {
        free(rstr_s1);
        rstr_s1 = NULL;
    }
    //GEN_BUILTIN
    int64_t b_i2;
    memcpy(&b_i2, futag_pos, sizeof(int64_t));
    futag_pos += sizeof(int64_t);
    
    struct json_object * FutagRefVarrfN = json_object_new_int64(b_i2 );
    //GEN_BUILTIN
    int64_t b_i3;
    memcpy(&b_i3, futag_pos, sizeof(int64_t));
    futag_pos += sizeof(int64_t);
    
    struct json_object * FutagRefVargXe = json_object_new_int64(b_i3 );
    //GEN_BUILTIN
    int32_t b_i4;
    memcpy(&b_i4, futag_pos, sizeof(int32_t));
    futag_pos += sizeof(int32_t);
    
    struct json_object * FutagRefVarwSm = json_object_new_int(b_i4 );
    //GEN_CSTRING
    char * rstr_s5 = (char *) malloc(dyn_cstring_size[2] + 1);
    memset(rstr_s5, 0, dyn_cstring_size[2] + 1);
    memcpy(rstr_s5, futag_pos, dyn_cstring_size[2] );
    futag_pos += dyn_cstring_size[2];
    const char * str_s5 = rstr_s5;
    
    struct json_object * FutagRefVar4Ic = json_object_new_string(str_s5 );
    //FREE
    if (rstr_s5) {
        free(rstr_s5);
        rstr_s5 = NULL;
    }
    const char * key7 = "dataHash";
    //FUNCTION_CALL
    json_object_object_add(body ,key7 ,FutagRefVarOuS );
    const char * key10 = "token";
    //FUNCTION_CALL
    json_object_object_add(body ,key10 ,FutagRefVar1U8 );
    const char * key13 = "exchangeStart";
    //FUNCTION_CALL
    json_object_object_add(body ,key13 ,FutagRefVarrfN );
    const char * key16 = "exchangeEnd";
    //FUNCTION_CALL
    json_object_object_add(body ,key16 ,FutagRefVargXe );
    const char * key19 = "exchangeResultCode";
    //FUNCTION_CALL
    json_object_object_add(body ,key19 ,FutagRefVarwSm );
    const char * key22 = "exchangeResultMessage";
    //FUNCTION_CALL
    json_object_object_add(body ,key22 ,FutagRefVar4Ic );
    //FUNCTION_CALL
    json_object_put(body );
    return 0;
}
// Compile database: 
/*
command: /home/russell/Futag/futag-llvm/bin/clang -D_GNU_SOURCE -Djson_c_EXPORTS -I/home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414 -I/home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/.futag-build -g -O0 -fsanitize=address -fprofile-instr-generate -fcoverage-mapping  -ffunction-sections -fdata-sections -Werror -Wall -Wcast-qual -Wno-error=deprecated-declarations -Wextra -Wwrite-strings -Wno-unused-parameter -Wstrict-prototypes -g -fPIC   -D JSON_C_DLL -D_REENTRANT -o CMakeFiles/json-c.dir/json_object.c.o -c /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/json_object.c
location: /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/.futag-build
file: /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/json_object.c
*/

// Compile command:
/* 
/home/russell/Futag/futag-llvm/bin/clang++ -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/ -I/home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/.futag-build/ /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/futag-context-fuzz-drivers/succeeded/json_object_put/json_object_put.1/json_object_put.1.c -o /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/futag-context-fuzz-drivers/succeeded/json_object_put/json_object_put.1/json_object_put.1.out -Wl,--start-group /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/.futag-install/lib/libjson-c.a /home/russell/Futag-tests/json-c-contexts/json-c-json-c-0.16-20220414/.futag-build/libjson-c.a -Wl,--end-group 
 */

// Error log:
/* 
clang-14: warning: treating 'c' input as 'c++' when in C++ mode, this behavior is deprecated [-Wdeprecated]

 */
