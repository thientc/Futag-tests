# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 
import time 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm"

lib_path = "libpq-standalone-REL_15_1"
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
        # target_type=AFLPLUSPLUS
    )
    generator.gen_targets(anonymous=True, max_wrappers=1000)
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    f.write("\n")

    start = time.time()
    generator.compile_targets(workers=16, keep_failed=True, coverage=True)
    end = time.time()
    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")

fuzzer = Fuzzer( # модуль для фаззинга
    FUTAG_PATH,
    fuzz_driver_path="libpq-standalone-REL_15_1/futag-fuzz-drivers/", 
    totaltime=5, # время фаззинга одной обертки
    fork=1, coverage=True,
    debug=True,
    timeout=3
)
fuzzer.fuzz() # функция для запуска фаззинга
