# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

import os 

from futag.preprocessor import *
from futag.generator import * 

os.chdir("LuaJIT")

lib_test = Builder(
    "../../futag-llvm-package/", 
    ".", 
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    "../../futag-llvm-package/", 
    ".",
    )
lib_test.gen_targets()
lib_test.compile_targets()

print("-- [Futag]: fuzz-drivers are saved in LuaJIT/futag-fuzz-targets!")