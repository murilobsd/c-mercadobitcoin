CFLAGS+=        -I../ -Iunity/src \
		-I/usr/local/include

LDFLAGS+=	unity/build/src/libunity.a -L/usr/local/lib -ljansson

LIB=		../mbc.a
SCRIPT_TEST=	all_tests.sh

OUT=		test_json\
		test_ticker\
		test_trade\
		test_order\
		test_orderbook\
		test_day_summary

test_day_summary:
	${CC} ${CFLAGS} test_day_summary.c $(LIB) -o $@ $(LDFLAGS)

test_json:
	${CC} ${CFLAGS} test_json.c $(LIB) -o $@ $(LDFLAGS)

test_ticker:
	${CC} ${CFLAGS} test_ticker.c $(LIB) -o $@ $(LDFLAGS)

test_trade:
	${CC} ${CFLAGS} test_trade.c $(LIB) -o $@ $(LDFLAGS)

test_order:
	${CC} ${CFLAGS} test_order.c $(LIB) -o $@ $(LDFLAGS)

test_orderbook:
	${CC} ${CFLAGS} test_orderbook.c $(LIB) -o $@ $(LDFLAGS)

all: $(OUT)
	@sh $(SCRIPT_TEST) -v

clean:
	rm -f $(OUT)
