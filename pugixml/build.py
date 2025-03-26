# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
import time 
FUTAG_PATH = "/home/futag/Futag/futag-llvm"
lib_path = "pugixml"

with open("result.ini", "a") as f :
    start = time.time()
    test_build = Builder(
        FUTAG_PATH,
        lib_path,
        clean=True,
        processes=16
    )
    test_build.auto_build()
    test_build.analyze()
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
    generator.gen_targets()
    
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    f.write("\n")

    start = time.time()
    generator.compile_targets(keep_failed=True)
    end = time.time()
    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")

print("-- [Futag]: fuzz-drivers are saved in pugixml/futag-fuzz-drivers!")
