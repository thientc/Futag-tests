//1342375166
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

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(uint8_t * Fuzz_Data, size_t Fuzz_Size){
    FuzzedDataProvider provider(Fuzz_Data, Fuzz_Size);

    auto b_i = provider.ConsumeIntegral<int64_t>();
    json_object_new_int64(b_i );
    return 0;
}
// Compile database: 
/*
command: /home/thientc/Futag/futag-llvm/bin/clang -D_GNU_SOURCE -Djson_c_EXPORTS -I/home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915 -I/home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/.futag-build -g -O0 -fsanitize=address -fprofile-instr-generate -fcoverage-mapping  -ffunction-sections -fdata-sections -Werror -Wall -Wcast-qual -Wno-error=deprecated-declarations -Wextra -Wwrite-strings -Wno-unused-parameter -Wstrict-prototypes -g -fPIC   -D JSON_C_DLL -D_REENTRANT -o CMakeFiles/json-c.dir/json_object.c.o -c /home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/json_object.c
location: /home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/.futag-build
file: /home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/json_object.c
*/

// Compile command:
/* 
/home/thientc/Futag/futag-llvm/bin/clang++ -fsanitize=address,fuzzer -fprofile-instr-generate -fcoverage-mapping  -g -O0 -ferror-limit=1 -I/home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915 -I/home/thientc/Futag-tests/json-c -I/home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/.futag-build  /home/thientc/Futag-tests/FuzzDataProvider/json_object_new_int64.1.c -o /home/thientc/Futag-tests/FuzzDataProvider/json_object_new_int64.1.c.out -Wl,--start-group /home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/.futag-build/libjson-c.a /home/thientc/Futag-tests/json-c/json-c-json-c-0.18-20240915/.futag-install/lib/libjson-c.a -Wl,--end-group  */

// Error log:
/* 

 */
