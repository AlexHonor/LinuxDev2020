.PHONY: all clean distclean

GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so *.txt prog prog-a prog-
CFLAGS = -Wall -fPIC

%.o: %.c
	cc $< $(CFLAGS) -c -o $@

all: README prog prog-a prog-so

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc -shared  $^ -o $@

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

distclean: clean
	rm -rf $(GENERATES)

gcov:
	gcov .libs/libbuf  