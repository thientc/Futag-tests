# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"

lib_path = "libpq-standalone-REL_15_1"
build_test = Builder(
    FUTAG_PATH,
    lib_path,
    clean=True,
    processes=16
)
build_test.auto_build()
build_test.analyze()

generator = Generator(
    FUTAG_PATH, 
    lib_path,
)
generator.gen_targets()
generator.compile_targets(workers=16, keep_failed=True)

fuzzer = Fuzzer( # модуль для фаззинга
    FUTAG_PATH,
    fuzz_driver_path="libpq-standalone-REL_15_1/futag-fuzz-drivers/", 
    totaltime=10, # время фаззинга одной обертки
    fork=4
)
fuzzer.fuzz() # функция для запуска фаззинга