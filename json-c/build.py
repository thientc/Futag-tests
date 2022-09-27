#!/home/thientc/python-venv/bin/python

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

lib_test = Builder(
    "/home/futag/Futag-tests/futag-llvm-package/", 
    "json-c",
    COMPILER_FLAGS,
    True,
    BUILD_PATH,
    INSTALL_PATH,
    ANALYSIS_PATH,
    16,
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    "/home/futag/Futag-tests/futag-llvm-package/", 
    "json-c",
    )
lib_test.gen_targets()
lib_test.compile_targets(True, 16)

# print("-- [Futag]: fuzz-drivers are saved in json-c/futag-fuzz-targets!")
