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
#include <stdlib.h>
#include <string.h>

#include "mb/utils.h"

double
xstrtod(const char *strnum, MBError *err)
{
	double result;
	char *endptr;

	result = strtod(strnum,  &endptr);

	if (result == 0) {
		if (errno == ERANGE) {
			debug("Out of range convert %s to double", strnum);
			*err = MBE_ERANGE;
		} else {
			debug("Failed convert %s to double", strnum);
			*err = MBE_CONVERT_STRTOD;
		}
	}

	return result;
}

const char *
get_coin_symbol(CoinType c)
{
	switch(c) {
	case BTC:
		return S_BTC;
	case LTC:
		return S_LTC;
	case BCH:
		return S_BCH;
	case XRP:
		return S_XRP;
	case ETH:
		return S_ETH;
	default:
		// TODO: return error no name coin;
		return S_BTC;
	}
}

/*
 * the join function helps in the creation of urls, a
 * array of string end a NULL value.
 */
char *
join(const char *sep, char **s_array)
{
	char *str;
	char *ptr;
	size_t i;
	size_t len;
	size_t sep_len;


	if (sep == NULL)
		sep = "";

	if (*s_array) {
		sep_len = strlen(sep);

		len = 1 + strlen(s_array[0]);
		for (i = 1; s_array[i] != NULL; i++)
			len += strlen(s_array[i]);
		len += sep_len * (i - 1);

		str = (char *)malloc(sizeof(char) * len);
		ptr = stpcpy(str, *s_array);
		for (i = 1; s_array[i] != NULL; i++) {
			ptr = stpcpy(ptr, sep);
			ptr = stpcpy(ptr, s_array[i]);
		}
	} else
	    	str = strdup("");
	return str;	
}
