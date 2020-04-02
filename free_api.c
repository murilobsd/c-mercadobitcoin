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

#include <stdlib.h>
#include <err.h>

#include <curl/curl.h>
#include <json-c/json.h>

#include "free_api.h"

typedef struct {
	FreeApiMethods *methods;

	/* internals */
	CURLcode code;
	long status_cde;
	/* struct response */
} FreeApiImpl;

static MBData	ticker(FreeApi *, CoinType);

static FreeApiMethods 	freeapi_impl_methods = {
	ticker
};

MBData
ticker(FreeApi *f, CoinType c)
{
	MBData mb_data;
	Ticker *t = NULL;

	t = (Ticker *)malloc(sizeof(Ticker));
	
	if (t == NULL) {
		mb_data._type = TICKER;
		mb_data.size = 0;
		mb_data.error = MBE_NOMEM;
		mb_data.data.ticker = NULL;
		return mb_data;
	}

	// mount url /<coin>/ticker/

	// request check error status code or timeout

	mb_data._type = TICKER;
	mb_data.size = 1;
	mb_data.error = MBE_OK;
	mb_data.data.ticker = t;

	// parse_data pass mb_data and Implement reponse struct check error;
	return mb_data;
}

FreeApi *
freeapi_init() {
	FreeApiImpl *f;

	f = (FreeApiImpl *)malloc(sizeof(FreeApiImpl));
	if (f == NULL)
		err(1, "alloc free api");
	f->methods = &freeapi_impl_methods;

	return (FreeApi *)f;
};

void
clean_freeapi(FreeApi *f)
{
	if (f == NULL) return;
	free(f);
}
