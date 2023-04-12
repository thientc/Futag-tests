# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
import pathlib


FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm/"
lib_path = "opus-1.3.1"
# # os.chdir("libmpeg2-0.5.1")
# test_build = Builder(
#     FUTAG_PATH,
#     lib_path,
#     clean=False,
#     processes=16
# )
# # test_build.auto_build()
# test_build.analyze()

generator = Generator(
    FUTAG_PATH,
    lib_path,
)
# generator.gen_targets(anonymous=False)
for x in generator.tmp_output_path.glob("**/*.c"):
     with open(x.as_posix(), 'r+') as f:
        content = f.read()
        f.seek(0, 0)
        f.write("#define VAR_ARRAYS 1\n" + "#define USE_ALLOCA 1\n" + "#define NONTHREADSAFE_PSEUDOSTACK 1\n" + content)

generator.compile_targets(keep_failed=True, extra_include="-DHAVE_CONFIG_H -I/home/futag/Futag-tests/libopus/opus-1.3.1/src/")

print("-- [Futag]: fuzz-drivers are saved in opus-1.3.1/futag-fuzz-drivers!")
