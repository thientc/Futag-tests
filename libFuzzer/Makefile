default: all;

all:
	../futag-llvm-package/bin/clang++ -g -O1 -fsanitize=fuzzer,address fuzzme.cc
clean:
	rm a.out