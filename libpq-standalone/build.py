# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"

lib = "libpq-standalone-REL_14_4"
lib_test = Builder(
    FUTAG_PATH, 
    lib,
    processes=16
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH, 
    lib,
    )
lib_test.gen_targets()
lib_test.compile_targets(16)