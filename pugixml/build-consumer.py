# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
import time 
import os
FUTAG_PATH = "/home/futag/Futag/futag-llvm"
library_root = "../pugixml-1.12"

consumer_root = "consumer"
os.chdir(consumer_root)

build_test = ConsumerBuilder(
   FUTAG_PATH, 
   library_root,
   ".",
   clean=False,
   processes=16,
)
build_test.auto_build()
build_test.analyze()

from futag.generator import * 
from futag.fuzzer import * 

generator = ContextGenerator(
    FUTAG_PATH, 
    library_root, 
)
generator.gen_context()
generator.compile_targets(
    keep_failed=True,
)