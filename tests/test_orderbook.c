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

#include "orderbook.h"

const char *data = "{\"asks\":[[38349.98993,0.17634193],[38349.99,0.18999999],[38350,0.12942862],[38438.89421,0.26108263],[38438.89422,0.29529834],[38439,0.0996]],\"bids\":[[38250.94,1.44220045],[38234,0.01574933],[38220.01,0.02439612],[38200,0.33401958],[38199.99,0.00131],[38199.98,0.11]]}";

void
setUp(void) {}

void
tearDown(void) {}

void
test_init_orderbook_fromjson_ok(void)
{
	OrderBookPtr ob;

	ob = init_orderbook_fromjson(data);
	
	TEST_ASSERT_NOT_NULL(ob);

	orderbook_free(ob);
}

int
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_init_orderbook_fromjson_ok);
	UNITY_END();
	return (0);
}

