# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

lib_test = Builder(
    "../futag-llvm-package/", 
    "curl",
    COMPILER_FLAGS,
    False, 
    BUILD_PATH, 
    INSTALL_PATH, 
    ANALYSIS_PATH, 
    4,
    "--without-ssl" 
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    "../futag-llvm-package/", 
    "curl",
)
lib_test.gen_targets()
lib_test.compile_targets()

print("-- [Futag]: fuzz-drivers are saved in curl/futag-fuzz-targets!")