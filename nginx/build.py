#!/home/thientc/python-venv/bin/python

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

FUTAG_PATH = "/home/futag/futag-llvm/"

lib_test = Builder(
    FUTAG_PATH, 
    "nginx",
    processes=16,
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH,
    "nginx", 
    build_path="."
)
lib_test.gen_targets()
lib_test.compile_targets(16)