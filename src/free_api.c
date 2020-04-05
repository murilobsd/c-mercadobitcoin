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
#include <string.h>

#include <curl/curl.h>
#include <jansson.h>

#include "mb/free_api.h"
#include "mb/http.h"
#include "mb/utils.h"
#include "mb/error.h"

#define SELF ((FreeApiImpl *)f)

typedef struct {
	FreeApiMethods *ops;

	/* internals */
	Resp resp; 		/* response */
	MBData data;		/* data */
	MBError error;
} FreeApiImpl;

static int		ticker(FreeApi *, CoinType);
static MBError		get_error(FreeApi *);
static MBError		parse_ticker(FreeApiImpl *);
static void		get_data(FreeApi *, void *);

static FreeApiMethods 	freeapi_impl_methods = {
	ticker,
	get_error,
	get_data,
};

static void
get_data(FreeApi *f, void *data)
{
	// 1. Checar se realmente a data existe?
	// 2. Checar qual e o tipo de dado
	// 3. Cast no dado
	Ticker *d = (Ticker *)data;

	/*TODO: implementar 1 */
	switch (SELF->data._type) {
	case TICKER:
		d->high = SELF->data.value.ticker.high;
		d->low = SELF->data.value.ticker.low;
		d->vol = SELF->data.value.ticker.vol;
		d->last = SELF->data.value.ticker.last;
		d->buy = SELF->data.value.ticker.buy;
		d->sell = SELF->data.value.ticker.sell;
		d->date	= SELF->data.value.ticker.date;
		break;
	default:
		debug("Dado não existe\n");
		break;
	}
}


static MBError
get_error(FreeApi *f)
{
	return SELF->error;
}

static MBError
parse_ticker(FreeApiImpl *f)
{	
	json_error_t error;
	json_t *root, *ticker, *high, *low, *vol, *last, *buy, *sell, *date;
	double highd, lowd, vold, lastd, buyd, selld;
	int datei;
	MBError err = MBE_OK;


	root = json_loads(f->data.raw, 0, &error);
	
	if (!root) {
		debug("error: on line %d: %s\n", error.line, error.text);
		err = MBE_PARSE_JSON;
		goto error;
	}

	if (!json_is_object(root)) {
		debug("error: root is not a object");
		err = MBE_PARSE_JSON;
		goto error;
	}
	ticker = json_object_get(root, "ticker");
	if (!json_is_object(ticker)) {
		debug("error: ticker is not a object");
		err = MBE_PARSE_JSON;
		goto error;
	}

	/* apartir desse momento estamos dentro da estrutura do ticker */
	high = json_object_get(ticker, "high");
	if (!json_is_string(high)) {
		debug("error: high is not a string\n");
		err = MBE_PARSE_JSON;
		goto error;
	}

	low = json_object_get(ticker, "low");
	if (!json_is_string(low)) {
		debug("error: low is not a string\n");
		err = MBE_PARSE_JSON;
		goto error;
	}
	vol = json_object_get(ticker, "vol");
	if (!json_is_string(vol)) {
		debug("error: vol is not a string\n");
		err = MBE_PARSE_JSON;
		goto error;
	}
	last = json_object_get(ticker, "last");
	if (!json_is_string(last)) {
		debug("error: last is not a string\n");
		err = MBE_PARSE_JSON;
		goto error;
	}
	buy = json_object_get(ticker, "buy");
	if (!json_is_string(buy)) {
		debug("error: buy is not a string\n");
		err = MBE_PARSE_JSON;
		goto error;
	}
	sell = json_object_get(ticker, "sell");
	if (!json_is_string(sell)) {
		debug("error: sell is not a string\n");
		err = MBE_PARSE_JSON;
		goto error;
	}
	date = json_object_get(ticker, "date");
	if (!json_is_integer(date)) {
		debug("error: date is not a integer\n");
		err = MBE_PARSE_JSON;
		goto error;
	}

	highd = xstrtod(json_string_value(high), &err);
	lowd = xstrtod(json_string_value(low), &err);
	vold = xstrtod(json_string_value(vol), &err);
	lastd = xstrtod(json_string_value(last), &err);
	buyd = xstrtod(json_string_value(buy), &err);
	selld = xstrtod(json_string_value(sell), &err);
	datei = (int)json_integer_value(date);

	if (err != MBE_OK) {
		debug("Erro: %s\n", mb_error_str(err));
		goto error;
	}

	// setamos date
	f->data.value.ticker.high = highd;
	f->data.value.ticker.low = lowd;
	f->data.value.ticker.vol = vold;
	f->data.value.ticker.last = lastd;
	f->data.value.ticker.buy = buyd;
	f->data.value.ticker.sell = selld;
	f->data.value.ticker.date = datei;
	f->data.length = 1;
	f->data._type = TICKER;

error:
	/* TODO: melhorar isso */
	if (root) {
		json_decref(root);
	}

	return err;
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
	debug("request url: %s\n", url);

	err = http_get(url, &SELF->resp);

	if (err != MBE_OK) {
		debug("failed request sticker\n");
		SELF->error = err;
		//goto err;
		return -1;
	}

	// precisamos setar os dados obtidos no reponse e limparmos depois o
	// response, agora temos o dado retornado pela api no MBdata
	SELF->data.raw = strdup(SELF->resp.data);
	SELF->data.length = 1; // isso porque a api retorna somente um dado;
	// caso fosse um array teríamos que colocar a quantidade retornado
	// pela api como será o caso do orderbook (1000)

	err = parse_ticker(SELF);

//err:
	if(url != NULL)
		free(url);
	/* isso deveria ser feito pela clean_freeapi() */
	return 0;
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

	return (FreeApi *)f;
};

void
clean_freeapi(FreeApi *f)
{
	if (SELF == NULL) return;
	if(SELF->resp.data != NULL) {
		SELF->resp.size = 0;
		SELF->resp.offset = 0;
		SELF->resp.status_code = 0;
		free(SELF->resp.data);
	}
	if(SELF->data.raw != NULL) {
		free(SELF->data.raw);
	}
	free(f);
}
