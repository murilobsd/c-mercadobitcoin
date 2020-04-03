CC=		cc
DEBUG=		-DDEBUG -g
HDRS=		free_api.h http.h utils.h types.h
SRCS=		free_api.c http.c utils.c
OBJS=		free_api.o http.o utils.o
LIB=		mercadobitcoin
CFLAGS=		-Iinclude/ -I/usr/local/include 
# CFLAGS+=	-Wall -Werror -Wextra
TFLAGS=		-R --exclude=.git --exclude=mb* --language-force=c .

VALGRIND=	/usr/local/bin/valgrind
VALGRINOPTS=	--track-origins=yes --keep-stacktraces=alloc-and-free

free_api.o:
	$(CC) -c src/free_api.c $(CFLAGS)
http.o:
	$(CC) -c src/http.c $(CFLAGS)
utils.o:
	$(CC) -c src/utils.c $(CFLAGS)
error.o:
	cc -c error.c -I/usr/local/include -I.

debug: CFLAGS += $(DEBUG)
debug: example

example: free_api.o utils.o http.o
	cc examples/main.c free_api.o utils.o http.o $(CFLAGS) \
		-o examples/app -L/usr/local/lib -lcurl -ljson-c
clean:
	rm -f *.o *.a *.core examples/app *.gcov *.gcno
tags:
	ectags $(TFLAGS)

valgrind: example
	$(VALGRIND) $(VALGRINDOPTS) examples/app
