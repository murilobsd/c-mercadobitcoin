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

#include <stdio.h>
#include <stdlib.h>
#include "unity.h"

#include "json.h"

const char *data = "{\"ticker\":{\"high\":\"37700.00000000\",\"low\":\"35260.00000000\",\"vol\":\"368.90539471\",\"last\":\"37132.55014000\",\"buy\":\"37132.55014000\",\"sell\":\"37298.99997000\",\"open\":\"35456.24000000\",\"date\":1586196838}}";


json_t *root;

void setUp() {}

void tearDown() {}

void
test_json_get_integer_ok(void)
{
	json_t *node;

	node = json_object_get(root, "ticker");
	int value = json_get_integer(node, "date");

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(node);

	TEST_ASSERT_EQUAL_INT(1586196838, value);
}

void
test_json_get_double_str_ok(void)
{
	json_t *node;

	node = json_object_get(root, "ticker");
	double value = json_get_double_str(node, "high");

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(node);

	TEST_ASSERT_EQUAL_DOUBLE(37700.00000000, value);

}

void
test_json_get_string_ok(void)
{
	json_t *node;

	node = json_object_get(root, "ticker");
	const char *obj = json_get_string(node, "high");

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(node);
	TEST_ASSERT_NOT_NULL(obj);

	TEST_ASSERT_EQUAL_STRING("37700.00000000", obj);
}

void
test_json_parse_str_ok(void)
{
	root = json_parse_str(data);
	
	TEST_ASSERT_NOT_NULL(root);
}

void
test_json_get_obj_ok(void)
{
	json_t *obj;

	obj = json_get_obj(root, "ticker");

	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(obj);
}


int
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_json_parse_str_ok);
	RUN_TEST(test_json_get_obj_ok);
	RUN_TEST(test_json_get_string_ok);
	RUN_TEST(test_json_get_double_str_ok);
	RUN_TEST(test_json_get_integer_ok);
	UNITY_END();
	json_free(root);
	return (0);
}
