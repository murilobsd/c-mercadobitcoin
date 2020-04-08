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
#include <string.h>
#include <stdio.h>

#include <jansson.h>

#include "day_summary.h"
#include "json.h"

#define MOD_NAME 	"day-summary"
#define SELF 		((struct day_summary_t *)d)
#define DEF_VAL_ERR	0.0

struct day_summary_t {
	char            *date;
	double 		opening;
	double 		closing;
	double 		lowest;
        double          highest;
	double 		volume;
	double 		quantity;
        int             amount;
        double          avg_price;
};

static DaySummaryPtr 	init_day_summary(void);
static void		day_summary_set_amount(struct day_summary_t *, int);
static void		day_summary_set_avg_price(struct day_summary_t *, double);
static void		day_summary_set_closing(struct day_summary_t *, double);
static void		day_summary_set_date(struct day_summary_t *, const char *);
static void		day_summary_set_highest(struct day_summary_t *, double);
static void		day_summary_set_lowest(struct day_summary_t *, double);
static void		day_summary_set_opening(struct day_summary_t *, double);
static void		day_summary_set_volume(struct day_summary_t *, double);
static void		day_summary_set_quantity(struct day_summary_t *, double);


int
day_summary_get_amount(DaySummaryPtr d)
{
        if (SELF != NULL)
                return SELF->amount;
        else
                return 0;
}

static void
day_summary_set_amount(struct day_summary_t *d, int data)
{
	d->amount = data;
}

static void
day_summary_set_avg_price(struct day_summary_t *d, double data)
{
	d->avg_price = data;
}

static void
day_summary_set_closing(struct day_summary_t *d, double data)
{
	d->closing = data;
}

static void
day_summary_set_date(struct day_summary_t *d, const char *data)
{
	d->date = strdup(data);
}

static void
day_summary_set_highest(struct day_summary_t *d, double data)
{
	d->highest = data;
}

static void
day_summary_set_lowest(struct day_summary_t *d, double data)
{
	d->lowest = data;
}

static void
day_summary_set_opening(struct day_summary_t *d, double data)
{
	d->opening = data;
}

static void
day_summary_set_volume(struct day_summary_t *d, double data)
{
	d->volume = data;
}

static void
day_summary_set_quantity(struct day_summary_t *d, double data)
{
	d->quantity= data;
}

DaySummaryPtr
init_day_summary_fromjson(const char *datastr)
{
	DaySummaryPtr   d = NULL;
	json_t          *root;
        int             amount;
	double          avg_price, opening, closing, highest;
        double          lowest, volume, quantity;
	
	if (datastr == NULL)
		return NULL;

	if ((root = json_parse_str(datastr)) == NULL)
		return NULL;

	/* init day_summary object */
	d = init_day_summary();

	/* get values from json */
	const char *date = json_get_string(root, "date");
	opening = json_get_double(root, "opening");
	closing = json_get_double(root, "closing");
	lowest = json_get_double(root, "lowest");
        highest = json_get_double(root, "highest");
	volume = json_get_double(root, "volume");
	quantity = json_get_double(root, "quantity");
        amount = json_get_integer(root, "amount");
        avg_price = json_get_double(root, "avg_price");

	/* set values */
        day_summary_set_date(SELF, date);
        day_summary_set_opening(SELF, opening);
        day_summary_set_closing(SELF, closing);
        day_summary_set_lowest(SELF, lowest);
	day_summary_set_highest(SELF, highest);
        day_summary_set_volume(SELF, volume);
        day_summary_set_quantity(SELF, quantity);
        day_summary_set_amount(SELF, amount);
        day_summary_set_avg_price(SELF, avg_price);

	/* decrement ref */
	json_free(root);

	return d;
}

static DaySummaryPtr
init_day_summary(void)
{
	DaySummaryPtr obj;

	obj = (DaySummaryPtr)malloc(sizeof(struct day_summary_t));

	if (obj == NULL)
		err(1, NULL);

	return obj;
}

void
day_summary_free(DaySummaryPtr *d)
{
	if (d != NULL) {
                if (SELF->date != NULL) free(SELF->date);
		free(*d);
		*d = NULL;
	}
}

const char *
day_summary_get_modname(void)
{
	return MOD_NAME;
}
