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

#include <errno.h>

#include "json.h"

static double xstrtod(const char *);

static double
xstrtod(const char *strnum)
{
	double result;
	char *endptr;

	result = strtod(strnum,  &endptr);

	if (result == 0) {
		if (errno == ERANGE) {
			return 0.0;
		} else {
			return 0.0;
		}
	}

	return result;
}

int
json_get_integer(json_t *node, const char *nodename)
{
	json_t *obj;
	int value;

	obj = json_object_get(node, nodename);

	if (!json_is_integer(obj))
		json_free(node);

	value = json_integer_value(obj);
	return value;
	
}

double
json_get_double_str(json_t *node, const char *nodename)
{
	double value = 0.0;
	const char *num_str = json_get_string(node, nodename);

	if (num_str == NULL)
		json_decref(node);

	value = xstrtod(num_str);

	return value;
}

const char *
json_get_string(json_t *node, const char *nodename)
{
	json_t *obj;

	obj = json_object_get(node, nodename);

	if (!json_is_string(obj))
		json_free(node);

	const char *str = json_string_value(obj);
	return str;
	
}

void
json_free(json_t *root)
{
	if (root != NULL)
		json_decref(root);
}

json_t *
json_get_obj(json_t *node, const char *nodename)
{
	json_t *obj;

	obj = json_object_get(node, nodename);

	if (!json_is_object(obj))
		json_free(node);

	return obj;
}

json_t *
json_parse_str(const char *data)
{
	json_error_t error;
	json_t *root = NULL;

	root = json_loads(data, 0, &error);

	if (root == NULL)
		printf("error: on line %d: %s\n", error.line, error.text);

	/* TODO: change this sometimes array object */
	if (json_is_object(root) == 0)
		json_free(root);

	return root;
}
