# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 
import os
import time 

FUTAG_PATH = "/home/futag/Futag/futag-llvm"

os.chdir("openssl-1.1.1s")
lib_path="."
with open("result.ini", "a") as f :
    start = time.time()
    build_test = Builder(
        FUTAG_PATH,
        lib_path,
        clean=False,
        build_path=lib_path,
        processes=16
    )
    build_test.auto_build()
    build_test.analyze()
    end = time.time()
    f.write("- Analyzing time: ")
    f.write(str(end - start))
    f.write("\n")

    start = time.time()
    generator = Generator(
        FUTAG_PATH,
        lib_path,
        build_path=lib_path,
    )
    generator.gen_targets()
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    f.write("\n")
    start = time.time()
    generator.compile_targets(workers=16, keep_failed=True)
    end = time.time()
    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")