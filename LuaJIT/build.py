# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

import os 

from futag.preprocessor import *
from futag.generator import * 

os.chdir("LuaJIT")
FUTAG_PATH = "/home/futag/futag-llvm/"

lib_test = Builder(
    FUTAG_PATH,
    ".", 
    COMPILER_FLAGS,
    False,
    ".", INSTALL_PATH, ANALYSIS_PATH, 16
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH,
    ".",LIBFUZZER,ANALYSIS_FILE_PATH, FUZZ_DRIVER_PATH, "."
)
lib_test.gen_targets()
lib_test.compile_targets(16)

# print("-- [Futag]: fuzz-drivers are saved in LuaJIT/futag-fuzz-targets!")