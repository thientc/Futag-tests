# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.fuzzer import * 
import os
FUTAG_PATH = "/home/futag/Futag/futag-llvm"

os.chdir("librdkafka-1.9.2")
lib_path="."
build_test = Builder(
     FUTAG_PATH,
     lib_path,
     clean=False,
     processes=16,
     build_path=lib_path
 )
build_test.auto_build()
build_test.analyze()

generator = Generator(
    FUTAG_PATH,
    lib_path,
    build_path=lib_path
)
generator.gen_targets()
generator.compile_targets(workers=4, keep_failed=True)
