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
#include <err.h>

#include <curl/curl.h>
#include <json-c/json.h>

#include "mb/free_api.h"
#include "mb/http.h"
#include "mb/utils.h"

#define SELF ((FreeApiImpl *)f)

typedef struct {
	FreeApiMethods *ops;

	/* internals */
	Resp resp; 		/* response */
	MBData *data;		/* data */
} FreeApiImpl;

static void		ticker(FreeApi *, CoinType);

static FreeApiMethods 	freeapi_impl_methods = {
	ticker
};

void
ticker(FreeApi *f, CoinType c)
{
	//Ticker *t = NULL;
	char *url;
	//const char *coin_symbol = get_coin_symbol(c);
	char *joins[] = {
	 	BASE_URL,	
		"BTC", "ticker", "", NULL
	};
/*
	t = (Ticker *)malloc(sizeof(Ticker));
	
	if (t == NULL) {
		mb_data._type = TICKER;
		mb_data.size = 0;
		mb_data.error = MBE_NOMEM;
		mb_data.data.ticker = NULL;
		return mb_data;
	}
*/
	// mount url /<coin>/ticker/
	url = join("/", joins);
	printf("%s\n", url);
	printf("%p\n", SELF->data);
	free(url);

	// TODO: clean ticker function switch ?
	// TODO: clean mbdata pointer switch ?
	// TODO: get type function!
	// TODO: raw data in mbdata

	// request check error status code or timeout
/*
	mb_data._type = TICKER;
	mb_data.size = 1;
	mb_data.error = MBE_OK;
	mb_data.data.ticker = t;
*/
	// parse_data pass mb_data and Implement reponse struct check error;
}

FreeApi *
freeapi_init() {
	FreeApiImpl *f;

	f = (FreeApiImpl *)malloc(sizeof(FreeApiImpl));
	if (f == NULL)
		err(1, "alloc free api");
	f->ops= &freeapi_impl_methods;

	return (FreeApi *)f;
};

void
clean_freeapi(FreeApi *f)
{
	if (f == NULL) return;
	free(f);
}
