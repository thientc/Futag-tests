#!/home/thientc/python-venv/bin/python

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"

lib_test = Builder(
    FUTAG_PATH,
    "php7",
    flags="-g -O0 -fsanitize=address",
    processes=16,
    build_ex_params=" --with-curl=shared --enable-exif=shared --enable-fileinfo=shared --enable-intl=shared --enable-mbstring=shared --enable-mbregex --with-openssl --with-mhash"
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_PATH,
    "php7",
)
lib_test.gen_targets()
lib_test.compile_targets(16)