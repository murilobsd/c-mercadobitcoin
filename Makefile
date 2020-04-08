.PHONY:	all
.SUFFIXES: .c .o

CFLAGS+=	-I/usr/local/include -g -std=c99 -Wall

OBJS+=		json.o \
		order.o \
		orderbook.o \
		ticker.o

.c.o:
	${CC} ${CFLAGS} -c $<

mbc.a: ${OBJS}
	$(AR) rs $@ ${OBJS}

all: mbc.a

tests: mbc.a
	$(MAKE) -C tests all
clean:
	rm -f *.o *.a *.core
