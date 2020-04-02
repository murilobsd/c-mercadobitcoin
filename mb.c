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
#include <string.h>
#include <err.h>

#include "mb.h"

static void 		 free_req(FreeReq *);
static void 		 free_resp(FreeResp *);
static void 		 free_ticker(FreeApi *, CoinType);
static const char 	*get_coin_str(CoinType);
static void		 Do(FreeApi *);

static void
Do(FreeApi *a)
{
	CURL *curl = NULL;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, a->url);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	} else {
		debug("deu pau");
	}
}


static size_t
recv_data_callback(char *ptr, size_t size, size_t nmemb, void *data)
{
	size_t ptrsize = nmemb*size;
	FreeApi *pr = (FreeApi *)data;
	pr->resp.data = (char *)realloc(pr->resp.data, 
		pr->resp.size + ptrsize + 1);

	if (pr->resp.data) {
		memcpy(&(pr->resp.data[pr->resp.size]), ptr, ptrsize);
		pr->resp.size += ptrsize;
		pr->resp.data[pr->resp.size] = '\0';
	}
	else {
		fprintf(stderr, "recv_data_callback: realloc failed\n");
	}

	return ptrsize;
}

/* Init FreeApi */
FreeApi *
free_api_init(void)
{
	FreeApi *fapi = NULL;

	debug("Init Free Api\n");

	if ((fapi = malloc(sizeof(FreeApi))) == NULL)
		err(1, "failed alloc api");
	
	/* init request */
	fapi->req.data= NULL;
	fapi->req.offset = NULL;
	fapi->req.size = 0;

	/* init response */
	fapi->resp.data= NULL;
	fapi->resp.offset = NULL;
	fapi->resp.size = 0;

	fapi->http_meth = GET;

	/* methods */
	fapi->ticker = free_ticker;

	return fapi;
};

static const char *
get_coin_str(CoinType c) {
	switch(c) {
	case BTC:
		return "BTC";
	case LTC:
		return "LTC";
	case BCH:
		return "BCH";
	case XRP:
		return "XRP";
	case ETH:
		return "ETH";
	default:
		return "BTC";
	}
}

/*
 * Retorna informações com o resumo das últimas 24 horas de negociações.
 */
static void
free_ticker(FreeApi *a, CoinType c)
{
	// https://www.mercadobitcoin.net/api/<coin>/ticker/"
	char buffer[1024];
	const char *met = "ticker"; // method name
	const char *coin = get_coin_str(c);

	int ret = snprintf(buffer, sizeof(buffer), FREE_API_URL, coin, met);

	if (ret < 0 || ret >= sizeof(buffer)) {
		err(1, "free ticker long url");
		free_api_clean(a);
	}

	//debug("Method: [%s] Coin: [%d]\n", met, c);
	//debug("url: [%s]\n", buffer);

	a->url = strdup(buffer);

	debug("url: [%s]\n", a->url);
	debug("method http: [%d]\n", a->http_meth);

	Do(a);
		
	return;
}

void
free_api_clean(FreeApi *a)
{
	if (a == NULL) return;
	
	free_req(&a->req);
	free_resp(&a->resp);
	
	if (a->url != NULL)
		free(a->url);
	free(a);

	debug("Clean Free Api\n");
}

static void
free_req(FreeReq *r)
{
	debug("Clean request \n");
	if (r->data != NULL)
		free(r->data);
	if (r->offset != NULL)
		free(r->offset);
}

static void
free_resp(FreeResp *r)
{
	debug("Clean response\n");
	if (r->data != NULL)
		free(r->data);
	if (r->offset != NULL)
		free(r->offset);
}



void
msg(const char *m)
{
	printf("%s\n", m);
}
