# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 
from futag.fuzzer import * 
import time 
start = time.time()

FUTAG_PATH = "/home/futag/Futag/futag-llvm"
lib_path = "json-c-json-c-0.16-20220414"

with open("result.ini", "a") as f :
    start = time.time()
    build_test = Builder(
    FUTAG_PATH, 
        lib_path,
        clean=True,
        processes=16,
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
        lib_path, 
    )
    generator.gen_targets(max_wrappers=1000)
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    start = time.time()
    f.write("\n")
    generator.compile_targets(
        # coverage=True,
        keep_failed=True,
    )
    end = time.time()
    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")
