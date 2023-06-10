# Futag-tests (https://github.com/thientc/Futag-tests): testing repository for Futag.
# This file is distributed under the GPL v3 license (https://www.gnu.org/licenses/gpl-3.0.en.html).

from futag.preprocessor import * 
from futag.generator import * 
from futag.fuzzer import * 
import time 

FUTAG_PATH = "/home/futag/Futag-tests/futag-llvm"

lib_path = "pugixml"

#1. Анализировать pugixml
test_build = Builder(
    FUTAG_PATH,
    lib_path,
    clean=True,
    processes=16
)
test_build.auto_build()
test_build.analyze()

#2. Генерировать фаззинг-обертки

lib_test = NatchGenerator(
    FUTAG_PATH,
    lib_path,
    "args_info.json" #Путь к JSON-файлу
)

lib_test.parse_values() #парсить значения из Натча
lib_test.gen_targets()
lib_test.compile_targets(keep_failed=True)

fuzzer = NatchFuzzer( # модуль для фаззинга
    FUTAG_PATH,
    fuzz_driver_path="pugixml/futag-fuzz-drivers/", 
    totaltime=5, # время фаззинга одной обертки
    fork=1, 
    debug=True,
    timeout=3,
    svres=True
)
fuzzer.fuzz()