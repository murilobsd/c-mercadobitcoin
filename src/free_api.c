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
#include <jansson.h>

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
static void		parse_ticker(char *);

static FreeApiMethods 	freeapi_impl_methods = {
	ticker
};


static void
parse_ticker(char *data)
{	
	json_t *root;
	json_error_t error;
	json_t *high;
	json_t *ticker;
	const char *number; // sim era para ser um número decimal segundo api

	root = json_loads(data, 0, &error);
	
	if (!root) {
		fprintf(stdout, "error: on line %d: %s\n", error.line,
		error.text);
		return;
	}

	if (!json_is_object(root)) {
		debug("error: root is not a object");
		json_decref(root);
		return;
	}
	
	ticker = json_object_get(root, "ticker");
	if (!json_is_object(ticker)) {
		debug("error: ticker is not a object");
		json_decref(root);
		return;
	}

	high = json_object_get(ticker, "high");
	if (!json_is_string(high)) {
		debug("error: high is not a string\n");
		json_decref(root);
		return;
	}

	printf("Alta: %s\n", json_string_value(high));

	json_decref(root);
}

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
	
	http_get(url, &SELF->resp);
	
	printf("%s\n", SELF->resp.data);
	parse_ticker(SELF->resp.data);

	free(url);
	free(SELF->resp.data);

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

	/* init response */
	f->resp.data= NULL;
	f->resp.offset = NULL;
	f->resp.size = 0;


	return (FreeApi *)f;
};

void
clean_freeapi(FreeApi *f)
{
	if (f == NULL) return;
	free(f);
}
