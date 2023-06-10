# Генерация фаззинг-оберток для функций библиотеки с использованием данных анализатора Natch

- Установить Python-пакет:
```bash
$ pip install futag-2.0.5.tar.gz
```
- Запустить скрипт подготовки и скрип генерации:
```bash
$ ./prepare.sh
$ python build.py
```

Заменить путь к futag-llvm при необходимости.

Папка "CORPUS" находится под каталогом: library/futag-fuzz-drivers/Natch_corpus