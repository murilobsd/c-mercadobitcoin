CFLAGS+=        -I../ -Iunity/src \
		-I/usr/local/include

LDFLAGS+=	unity/build/src/libunity.a -L/usr/local/lib -ljansson

LIB=		../mbc.a
SCRIPT_TEST=	all_tests.sh

test_json:
	${CC} ${CFLAGS} test_json.c $(LIB) -o $@ $(LDFLAGS)

all: test_json
	@sh $(SCRIPT_TEST) -v
