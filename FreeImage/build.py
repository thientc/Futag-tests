# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

import os

from futag.preprocessor import *
from futag.generator import * 

os.chdir("FreeImage")
FUTAG_PATH = "/home/futag/Futag/futag-llvm"
lib_path = "."
build_test = Builder(
    FUTAG_PATH, 
    lib_path,
    clean=False,
    build_path=lib_path,
    processes=4
)
build_test.auto_build()
build_test.analyze()

# generator = Generator(
#     FUTAG_PATH, 
#     lib_path,
#     build_path=lib_path,
# )
# generator.gen_targets()
# generator.compile_targets(4)

print("-- [Futag]: fuzz-drivers are saved in FreeImage/futag-fuzz-targets!")
