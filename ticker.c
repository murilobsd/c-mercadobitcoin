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

#include <err.h>
#include <stdint.h>
#include <stdlib.h>

#include <jansson.h>

#include "ticker.h"
#include "json.h"

#define MOD_NAME 	"ticker"
#define SELF 		((struct ticker_t *)t)
#define DEF_VAL_ERR	0.0

struct ticker_t {
	double 		buy;
	uint64_t 	date;
	double 		high;
	double 		last;
	double 		low;
	double 		sell;
	double 		vol;
};

static TickerPtr 	init_ticker(void);
static void		ticker_set_high(struct ticker_t *, double);
static void		ticker_set_low(struct ticker_t *, double);
static void		ticker_set_vol(struct ticker_t *, double);
static void		ticker_set_last(struct ticker_t *, double);
static void		ticker_set_buy(struct ticker_t *, double);
static void		ticker_set_sell(struct ticker_t *, double);
static void		ticker_set_date(struct ticker_t *, uint64_t);

static void
ticker_set_high(struct ticker_t *t, double data)
{
	t->high = data;
}

static void
ticker_set_low(struct ticker_t *t, double data)
{
	t->low = data;
}

static void
ticker_set_vol(struct ticker_t *t, double data)
{
	t->vol = data;
}

static void
ticker_set_last(struct ticker_t *t, double data)
{
	t->last = data;
}

static void
ticker_set_buy(struct ticker_t *t, double data)
{
	t->buy = data;
}

static void
ticker_set_sell(struct ticker_t *t, double data)
{
	t->sell = data;
}

static void
ticker_set_date(struct ticker_t *t, uint64_t data)
{
	t->date = data;
}

double
ticker_get_high(TickerPtr t) 
{
	if (t != NULL)
		return SELF->high;
	else
		return DEF_VAL_ERR;
}

double
ticker_get_low(TickerPtr t)
{
	if (t != NULL)
		return SELF->low;
	else
		return DEF_VAL_ERR;
}

double
ticker_get_vol(TickerPtr t)
{
	if (t != NULL)
		return SELF->vol;
	else
		return DEF_VAL_ERR;
}


double
ticker_get_last(TickerPtr t)
{
	if (t != NULL)
		return SELF->last;
	else
		return DEF_VAL_ERR;
}

double
ticker_get_buy(TickerPtr t)
{
	if (t != NULL)
		return SELF->buy;
	else
		return DEF_VAL_ERR;
}

double
ticker_get_sell(TickerPtr t)
{
	if (t != NULL)
		return SELF->sell;
	else
		return DEF_VAL_ERR;
}

uint64_t
ticker_get_date(TickerPtr t)
{
	if (t != NULL)
		return SELF->date;
	else
		return 0;
}

TickerPtr
init_ticker_fromjson(const char *datastr)
{
	TickerPtr t = NULL;
	json_t *root, *node_ticker;
	double buy, high, last, low, sell, vol;
	uint64_t date;
	
	if (datastr == NULL)
		return NULL;

	if ((root = json_parse_str(datastr)) == NULL)
		return NULL;

	if ((node_ticker = json_get_obj(root, MOD_NAME)) == NULL) {
		json_free(root);
		return NULL;
	}

	/* init ticker object */
	t = init_ticker();

	/* get values from json */
	buy = json_get_double_str(node_ticker, "buy");
	date = json_get_integer(node_ticker, "date");
	high = json_get_double_str(node_ticker, "high");
	last = json_get_double_str(node_ticker, "last");
	low = json_get_double_str(node_ticker, "low");
	sell = json_get_double_str(node_ticker, "sell");
	vol = json_get_double_str(node_ticker, "vol");

	/* set values */
	ticker_set_buy(SELF, buy);
	ticker_set_date(SELF, (uint64_t)date);
	ticker_set_high(SELF, high);
	ticker_set_last(SELF, last);
	ticker_set_low(SELF, low);
	ticker_set_sell(SELF, sell);
	ticker_set_vol(SELF, vol);

	/* decrement ref */
	json_free(root);

	return t;
}

static TickerPtr
init_ticker(void)
{
	TickerPtr obj;

	obj = (TickerPtr)malloc(sizeof(struct ticker_t));

	if (obj == NULL)
		err(1, NULL);

	return obj;
}

void
ticker_free(TickerPtr *t)
{
	if (t != NULL) {
		free(*t);
		*t = NULL;
	}
}

const char *
ticker_get_modname(void)
{
	return MOD_NAME;
}
