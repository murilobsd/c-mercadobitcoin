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

#include "order.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_init_order_ok(void)
{
	OrderPtr o;
	double price, qtd;

	o = init_order(10410.00006000, 2.09190016);
	
	price = order_get_price(o);
	qtd = order_get_quantity(o);

	TEST_ASSERT_NOT_NULL(o);
	TEST_ASSERT_EQUAL_DOUBLE(10410.00006000, price);
	TEST_ASSERT_EQUAL_DOUBLE(2.09190016, qtd);

	order_free(o);
}

int
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_init_order_ok);
	UNITY_END();
	return (0);
}