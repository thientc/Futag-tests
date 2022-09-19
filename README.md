# Futag-tests
This repository is for testing [Futag](https://github.com/ispras/Futag) on libraries and is distributed under [license GNU GPL v3](https://www.gnu.org/licenses/gpl-3.0.en.html). In case of bug discovery in testing libraries, please refer to [Futag repository](https://github.com/ispras/Futag).

## Get latest Futag package
- Run get-Futag.sh to get latest Futag
```bash
~/Futag-tests$ ./get-Futag.sh
```

- Install requirements:
```bash
~/Futag-tests$ pip install -r futag-llvm-package/python-package/requirements.txt
```

## Testing library
- Change directory to library
- Run prepare.sh to download and extract library's source code
- Run build.py to generate fuzz-driver for functions of library.

For example:
```bash
~/Futag-tests$ cd json-c
~/Futag-tests/json-c$ ./prepare.sh
~/Futag-tests/json-c$ python build.py
```
