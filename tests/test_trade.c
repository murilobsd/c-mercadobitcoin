/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <unity.h>

#include "trade.h"

const char *data = "[{\"tid\":5976675,\"date\":1586350825,\"type\":\"buy\",\"price\":38194.97999,\"amount\":0.00030606},{\"tid\":5976676,\"date\":1586350828,\"type\":\"buy\",\"price\":38194.97999,\"amount\":0.00078544},{\"tid\":5976677,\"date\":1586350829,\"type\":\"buy\",\"price\":38194.97999,\"amount\":0.01963608}]";

void
setUp(void) {}

void
tearDown(void) {}

void
test_init_trades_fromjson_ok(void)
{
	TradesPtr ts;

	ts = init_trades_fromjson(data);
	
	TEST_ASSERT_NOT_NULL(ts);
        TEST_ASSERT_EQUAL_INT(3, trades_get_size(ts));

	trades_free(ts);
}

int
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_init_trades_fromjson_ok);
	UNITY_END();
	return (0);
}

