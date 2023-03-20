# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 
from futag.fuzzer import * 

FUTAG_PATH = "/home/futag/Futag/futag-llvm"
library_root = "json-c-json-c-0.16-20220414"

build_test = Builder(
   FUTAG_PATH, 
   library_root,
   clean=True,
   processes=16,
)
build_test.auto_build()
build_test.analyze()

generator = Generator(
    FUTAG_PATH, 
    library_root, 
)

generator.gen_targets()
generator.compile_targets(
    keep_failed=True,
)

consumer_root = "libstorj-1.0.3"
build_consumer = ConsumerBuilder(
   FUTAG_PATH, 
   library_root,
   consumer_root,
   clean=True,
   processes=16,
)
build_consumer.auto_build()
build_consumer.analyze()

context_generator = ContextGenerator(
    FUTAG_PATH, 
    library_root, 
)
context_generator.gen_context()

context_generator.compile_targets(
    keep_failed=True,
)