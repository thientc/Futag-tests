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
lib_path = "."
test_build = Builder(
    FUTAG_PATH,  
    lib_path,
    clean=False, 
    build_path=lib_path, 
)
test_build.auto_build()
test_build.analyze()

generator = Generator(
    FUTAG_PATH, 
    lib_path,
    build_path=lib_path,
)
generator.gen_targets()
generator.compile_targets()

print("-- [Futag]: fuzz-drivers are saved in nDPI/futag-fuzz-drivers!")