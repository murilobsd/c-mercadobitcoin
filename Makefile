mb.o:
	cc -c mb.c -I/usr/local/include -I. 
example: mb.o
	cc examples/main.c mb.o -I/usr/local/include -I. \
		-o examples/app -L/usr/local/lib -lcurl
clean:
	rm -f *.o examples/app *.gcov *.gcno
tags:
	ectags mb.h mb.c

valgrind:
	valgrind examples/app
