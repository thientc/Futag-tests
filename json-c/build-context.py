# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *

FUTAG_PATH = "/home/futag/Futag/futag-llvm"
library_root = "json-c-json-c-0.16-20220414"
consumer_root = "libstorj-1.0.3"
build_test = ConsumerBuilder(
   FUTAG_PATH, 
   library_root,
   consumer_root,
   clean=True,
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