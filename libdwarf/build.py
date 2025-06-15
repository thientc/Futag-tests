# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 
from futag.fuzzer import * 

FUTAG_PATH = "/home/futag/Futag/futag-llvm"
lib_path = "libdwarf-2.0.0"
build_test = Builder(
   FUTAG_PATH, 
   lib_path,
   clean=True,
   processes=16,
)
build_test.build_meson()
build_test.analyze()

generator = Generator(
    FUTAG_PATH, 
    lib_path,
    target_type=LIBFUZZER
)

generator.gen_targets()
generator.compile_targets(
    coverage=True,
    keep_failed=True,
)

