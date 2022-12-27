# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib_path = "pugixml-1.12"

test_build = Builder(
    FUTAG_PATH,
    lib_path,
    processes=4
)
test_build.auto_build()
test_build.analyze()

generator = Generator(
    FUTAG_PATH,
    lib_path,
)
generator.gen_targets()
generator.compile_targets(4)

print("-- [Futag]: fuzz-drivers are saved in pugixml/futag-fuzz-targets!")
