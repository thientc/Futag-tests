# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib_path = "opencv-4.6.0"
build_test = Builder(
     FUTAG_PATH,
     lib_path,
     processes=4
 )
build_test.auto_build()
build_test.analyze()

generator = Generator(
    FUTAG_PATH,
    lib_path,
)
generator.gen_targets()
generator.compile_targets(4)

print("-- [Futag]: fuzz-drivers are saved in opencv-4.6.0/futag-fuzz-targets!")
