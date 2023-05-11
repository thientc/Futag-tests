# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 
import time 

FUTAG_PATH = "/home/futag/Futag/futag-llvm"

lib_path = "curl-7.85.0"
with open("result.ini", "a") as f :
    start = time.time()
    lib_test = Builder(
        FUTAG_PATH,
        lib_path,
        clean=True,
        intercept=True,
        processes=16,
        build_ex_params="--without-ssl" 
    )
    lib_test.auto_build()
    lib_test.analyze()
    end = time.time()
    f.write("- Analyzing time: ")
    f.write(str(end - start))
    f.write("\n")

with open("result.ini", "a") as f :
    start = time.time()
    lib_test = Generator(
        FUTAG_PATH,
        lib_path,

    )
    lib_test.gen_targets()
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    f.write("\n")

    start = time.time()
    lib_test.compile_targets(16, keep_failed=True, 
        extra_params="-DHAVE_CONFIG_H",
        extra_dynamiclink="-lgsasl -lpsl -lldap -lbrotlidec -lz -lidn2 -llber"
    )
    end = time.time()
    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")