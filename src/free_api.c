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
	MBError error;
} FreeApiImpl;

static int		ticker(FreeApi *, CoinType);
static MBError		get_error(FreeApi *);
static void		parse_ticker(char *);

static FreeApiMethods 	freeapi_impl_methods = {
	ticker,
	get_error,
};


static MBError
get_error(FreeApi *f)
{
	return SELF->error;
}

static void
parse_ticker(char *data)
{	
	json_t *root;
	json_error_t error;
	json_t *high;
	json_t *ticker;
	double high_d;
	MBError err = MBE_OK;

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

	const char *number = json_string_value(high);

	printf("Alta: %s\n", number);

	high_d = xstrtod(number, &err);

	if (err != MBE_OK)
		printf("Erro: %s\n", mb_error_str(err));
	else
		printf("Alta Double: %f\n", high_d);

	json_decref(root);
}

int
ticker(FreeApi *f, CoinType c)
{
	//Ticker *t = NULL;
	char *url;
	const char *coin_symbol = get_coin_symbol(c);
	const char *method_name = "ticker";
	MBError err = MBE_OK;

	const char *parts_url[5];

	parts_url[0] = BASE_URL;
	parts_url[1] = coin_symbol;
	parts_url[2] = method_name;
	parts_url[3] = "";
	parts_url[4] = NULL;

	// mount url /<coin>/ticker/
	url = join("/", parts_url);
	printf("%s\n", url);
	
	err = http_get(url, &SELF->resp);

	if (err != MBE_OK) {
		debug("error request sticker\n");
		SELF->error = err;
		goto err;
	}

	//parse_ticker(SELF->resp.data);

	free(url);
	free(SELF->resp.data);
	// TODO: get type function!
	// TODO: raw data in mbdata

	// request check error status code or timeout
	return 0;
err:
	if(url != NULL) free(url);
	if(SELF->resp.data != NULL) free(SELF->resp.data);
	return -1;
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

	/* error ok */
	f->error = MBE_OK;

	f->data = NULL;


	return (FreeApi *)f;
};

void
clean_freeapi(FreeApi *f)
{
	if (f == NULL) return;
	free(f);
}
