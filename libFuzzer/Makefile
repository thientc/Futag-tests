default: all;

all:
	../futag-llvm-package/bin/clang++ -g -O0 -fsanitize=fuzzer,address fuzzme.cc
clean:
	rm a.out