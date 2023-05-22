# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import *
from futag.generator import * 
import time 


FUTAG_PATH = "/home/futag/Futag/futag-llvm"
lib_path = "opus-1.3.1"
with open("result.ini", "a") as f :
    start = time.time()
    test_build = Builder(
        FUTAG_PATH,
        lib_path,
        clean=True,
        intercept=False,
        processes=16
    )
    test_build.auto_build()
    test_build.analyze()
    end = time.time()
    f.write("- Analyzing time: ")
    f.write(str(end - start))
    f.write("\n")

with open("result.ini", "a") as f :
    start = time.time()
    generator = Generator(
        FUTAG_PATH,
        lib_path,
    )
    generator.gen_targets(anonymous=False)
    end = time.time()
    f.write("- Generation time: ")
    f.write(str(end - start))
    f.write("\n")

    for x in generator.tmp_output_path.glob("**/*.c"):
        with open(x.as_posix(), 'r+') as fi:
            content = fi.read()
            fi.seek(0, 0)
            fi.write("#define VAR_ARRAYS 1\n" + "#define USE_ALLOCA 1\n" + "#define NONTHREADSAFE_PSEUDOSTACK 1\n" + content)
    
    start = time.time()
    generator.compile_targets(keep_failed=True, extra_include="/home/futag/Futag-tests/libopus/opus-1.3.1/.futag-build/ /home/futag/Futag-tests/libopus/opus-1.3.1/src/", extra_params="-DHAVE_CONFIG_H")
    end = time.time()

    f.write("- Compile time: ")
    f.write(str(end - start))
    f.write("\n")