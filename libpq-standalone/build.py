# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 

FUTAG_LLVM_PACKAGE_PATH = "/home/thientc/Futag/futag-llvm/"

lib_test = Builder(
    FUTAG_LLVM_PACKAGE_PATH, 
    "libpq-standalone",
    COMPILER_FLAGS,
    True,
    BUILD_PATH,
    INSTALL_PATH,
    ANALYSIS_PATH,
    16
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_LLVM_PACKAGE_PATH, 
    "libpq-standalone",
    )
lib_test.gen_targets()
lib_test.compile_targets(True, 16)

lib_test = Fuzzer(FUTAG_LLVM_PACKAGE_PATH, "libpq-standalone/" + FUZZ_DRIVER_PATH,True, False, True, 4, 60)
lib_test.fuzz()