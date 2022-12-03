# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib_path = "curl-7.85.0"
lib_test = Builder(
    FUTAG_PATH,
    lib_path,
    clean=True, 
    processes=1,
    build_ex_params="--without-ssl" 
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH,
    lib_path,
)
lib_test.gen_targets()
lib_test.compile_targets(16, extra_include="-DHAVE_CONFIG_H")

# print("-- [Futag]: fuzz-drivers are saved in curl/futag-fuzz-targets!")
