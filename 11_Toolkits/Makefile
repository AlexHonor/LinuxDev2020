all: freq

freq: freq.c
	gcc `pkg-config --cflags glib-2.0` freq.c `pkg-config --libs glib-2.0` -o freq
	 
clean:
	rm freq