# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib_path = "libvpx-1.13.0"
test_build = Builder(
    FUTAG_PATH,
    lib_path,
    clean=True,
    processes=16
)
test_build.auto_build()
test_build.analyze()

generator = Generator(
    FUTAG_PATH,
    lib_path,
)
# generator.gen_targets(anonymous=False)
generator.compile_targets(keep_failed=True, extra_include="-I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/third_party/googletest/src/include/gtest/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/third_party/libwebm/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/vp8/encoder/")

print("-- [Futag]: fuzz-drivers are saved in libmpeg2-0.5.1/futag-fuzz-drivers!")


# /home/futag/Futag-tests/futag-llvm/bin/clang++ -fsanitize=address,fuzzer -g -O0 -ferror-limit=1 -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/third_party/googletest/src/include/ -I/home/futag/Futag-tests/libvpx/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/ -I/home/futag/Futag-tests/libvpx/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/vp8/encoder/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/third_party/libwebm/ -I/home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/ /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-fuzz-drivers/vp9_cost_tokens_skip/vp9_cost_tokens_skip1/vp9_cost_tokens_skip1.c -o /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-fuzz-drivers/vp9_cost_tokens_skip/vp9_cost_tokens_skip1/vp9_cost_tokens_skip1.out -Wl,--start-group /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/libgtest_g.a /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/libgtest.a /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/libvpx.a /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/libvpxrc.a /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/libvpxrc_g.a /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-build/libvpx_g.a /home/futag/Futag-tests/libvpx/libvpx-1.13.0/.futag-install/lib/libvpx.a -Wl,--end-group 
