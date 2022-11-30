# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib_path = "libpng-1.6.35"
build_test = Builder(
    FUTAG_PATH, 
    lib_path,
    processes=8
)
build_test.auto_build()
build_test.analyze()

generator = Generator(
    FUTAG_PATH,
    lib_path)
generator.gen_targets()
generator.compile_targets(8, extra_syslink=" -lm -lz -lm ")
