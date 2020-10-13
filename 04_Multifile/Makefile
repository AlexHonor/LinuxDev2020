.PHONY: all clean prepare_tests create_test_dir test distclean

GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so *.txt
CFLAGS = -Wall -fPIC

%.o: %.c
	cc $< $(CFLAGS) -c -o $@

gen_data_%: %
	./$* > 0/$*.txt 2>&1
	./$* 1 > 1/$*.txt 2>&1
	./$* 1 2 3 > 3/$*.txt 2>&1

test_dir_%:
	-cmp $*/prog.txt $*/prog-a.txt
	-cmp $*/prog-a.txt $*/prog-so.txt
	-cmp $*/prog-so.txt $*/prog.txt
	
all: README prog prog-a prog-so

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared  $^ -o $@

create_test_dir: 
	mkdir -p 0
	mkdir -p 1
	mkdir -p 3

prepare_tests: create_test_dir gen_data_prog gen_data_prog-a gen_data_prog-so

test: prepare_tests test_dir_0 test_dir_1 test_dir_3

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a 
	cc $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so 
	cc -L. -Wl,-rpath,"./" prog.o -loutput -o $@

README: prog
	./$< 2> $@

fun.o: outlib.h

clean:
	rm -f $(TRASH)
	rm -f -r 0
	rm -f -r 1
	rm -f -r 3

distclean: clean
	rm -rf $(GENERATES)
