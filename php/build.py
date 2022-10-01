#!/home/thientc/python-venv/bin/python

# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
from futag.sysmsg import * 

FUTAG_LLVM_PACKAGE_PATH = "/home/futag/Futag-tests/futag-llvm/"

lib_test = Builder(
    FUTAG_LLVM_PACKAGE_PATH,
    "php7",
    "-g -O0 -fsanitize=address",
    True,
    BUILD_PATH,
    INSTALL_PATH,
    ANALYSIS_PATH,
    16,
    " --with-curl=shared --enable-exif=shared --enable-fileinfo=shared --enable-intl=shared --enable-mbstring=shared --enable-mbregex --with-openssl --with-mhash"
)
lib_test.auto_build()
lib_test.analyze()

lib_test = Generator(
    FUTAG_LLVM_PACKAGE_PATH,
    "php7",
)
lib_test.gen_targets()
lib_test.compile_targets(True, 16)