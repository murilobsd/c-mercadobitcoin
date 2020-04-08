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
#include "unity.h"

#include "json.h"

const char *data = "{\"ticker\":{\"high\":\"37700.00000000\",\"low\":\"35260.00000000\",\"vol\":\"368.90539471\",\"last\":\"37132.55014000\",\"buy\":\"37132.55014000\",\"sell\":\"37298.99997000\",\"open\":\"35456.24000000\",\"date\":1586196838}}";

const char *data_arr = "{\"asks\":[[37749.99,0.00257759],[37750,0.82968792],[37799.99998,0.00162446],[37800,0.01368256],[37896,0.0054],[37899.9399,0.00128477]]}";

const char *data_arr_arr = "[[37749.99,0.00257759],[37750,0.82968792],[37799.99998,0.00162446],[37800,0.01368256],[37896,0.0054],[37899.9399,0.00128477]]";


json_t *root;

void setUp() {}

void tearDown() {}

void
test_json_get_array_ok(void)
{
	json_t *arr, *root_arr;
	size_t size;

	root_arr = json_parse_str(data_arr);
	arr = json_get_array(root_arr, "asks", &size);

	TEST_ASSERT_NOT_NULL(root_arr);
	TEST_ASSERT_NOT_NULL(arr);

	TEST_ASSERT_EQUAL_INT(6, size);

	json_free(root_arr);
}

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
        json_t *root_arr;

	root = json_parse_str(data);
	root_arr = json_parse_str(data_arr_arr);
	
	TEST_ASSERT_NOT_NULL(root);
	TEST_ASSERT_NOT_NULL(root_arr);

        json_free(root_arr);
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
	RUN_TEST(test_json_get_array_ok);
	UNITY_END();
	json_free(root);
	return (0);
}
