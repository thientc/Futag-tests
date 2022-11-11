# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 
import os
FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib="openssl-1.1.1s"
os.chdir(lib)
# lib_test = Builder(
#      FUTAG_PATH,
#      ".",
#      build_path=".",
#      processes=16
#  )
# lib_test.auto_build()
# lib_test.analyze()

# lib_test = Generator(
#     FUTAG_PATH,
#     ".",
#     build_path=".",
# )
# lib_test.gen_targets()
# lib_test.compile_targets(16)

fuzzer = Fuzzer(
    FUTAG_PATH,
    "futag-fuzz-drivers",
    fork=4,
    totaltime=30,
    debug=True
)
fuzzer.fuzz()