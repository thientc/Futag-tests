# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 
import time 

FUTAG_PATH = "/home/futag/Futag/futag-llvm"
lib_path = "libpng-1.6.35"

with open("result.ini", "a") as f :
    start = time.time()
    build_test = Builder(
        FUTAG_PATH, 
        lib_path,
        processes=8
    )
    build_test.auto_build()
    build_test.analyze()
    end = time.time()
    f.write("- Analyzing time: ")
    f.write(str(end - start))
    f.write("\n")

with open("result.ini", "a") as f :
    start = time.time()
    generator = Generator(
        FUTAG_PATH,
        lib_path)
    generator.gen_targets()
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    f.write("\n")
    
    start = time.time()
    generator.compile_targets(16, keep_failed=True, extra_dynamiclink=" -lm -lz -lm ")
    end = time.time()
    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")