# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

import os

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 
os.chdir("nDPI")
FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"

lib_test = Builder(
    FUTAG_PATH,  
    ".",
    clean=False, 
    build_path=".", 
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH, 
    ".",
    build_path=".",
)
lib_test.gen_targets()
lib_test.compile_targets()

print("-- [Futag]: fuzz-drivers are saved in nDPI/futag-fuzz-targets!")