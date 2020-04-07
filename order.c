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
#include <stdlib.h>

#include "order.h"

#define MOD_NAME 	"order"
#define SELF 		((struct order_t *)o)
#define DEF_VAL_ERR	0.0

struct order_t {
	double price;
	double quantity;
        OrderType type;
};

void
order_set_type(struct order_t *o, OrderType t)
{
	o->type = t;
}

void
order_set_price(struct order_t *o, double data)
{
	o->price = data;
}

void
order_set_quantity(struct order_t *o, double data)
{
	o->quantity = data;
}

double
order_get_price(OrderPtr o) 
{
	if (o != NULL)
		return SELF->price;
	else
		return DEF_VAL_ERR;
}

double
order_get_quantity(OrderPtr o) 
{
	if (o != NULL)
		return SELF->quantity;
	else
		return DEF_VAL_ERR;
}

OrderType
order_get_type(OrderPtr o) 
{
	if (o != NULL)
		return SELF->type;
	else
		return OR_INVALID;
}

OrderPtr
init_order(OrderType t, double price, double qtd)
{
	OrderPtr o;

	o = (OrderPtr)malloc(sizeof(struct order_t));

	if (o == NULL)
		err(1, NULL);

	/* set values */
	order_set_price(SELF, price);
	order_set_quantity(SELF, price);
	order_set_type(SELF, t);

	return o;
}

void
order_free(OrderPtr *o)
{
	if (o != NULL) {
		free(*o);
                *o = NULL;
	}
}

const char *
order_get_modname(void)
{
	return MOD_NAME;
}
