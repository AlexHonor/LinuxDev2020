all: wrapper.c 
	gcc wrapper.c -fPIC -ldl -shared -o wrapper.so


test:
	export LD_PRELOAD="wrapper.so" rm
	touch dfasdqr
	touch asdasd_FIX_asdasd

	rm dfasdqr
	rm asdasd_FIX_asdasd

	test -e asdasd_FIX_asdasd

clean:
	rm -f *.so 
