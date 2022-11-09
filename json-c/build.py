#!/home/thientc/python-venv/bin/python

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib = "json-c-json-c-0.16-20220414"
lib_test = Builder(
   FUTAG_PATH, 
   lib,
   clean=True,
   processes=8,
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH, 
    lib)
lib_test.gen_targets()
lib_test.compile_targets(8)
