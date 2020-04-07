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

#ifndef _ORDER_H
#define _ORDER_H

typedef struct order_t * OrderPtr;

typedef enum {
        OR_ASK,
        OR_BID,
        OR_INVALID
} OrderType;

OrderPtr	init_order(OrderType, double, double);
void		order_free(OrderPtr *);
const char 	*order_get_modname(void);
double		order_get_price(OrderPtr);
double		order_get_quantity(OrderPtr);
OrderType       order_get_type(OrderPtr);
void		order_set_price(struct order_t *, double);
void		order_set_quantity(struct order_t *, double);
void		order_set_type(struct order_t *, OrderType);

#endif /* _ORDER_H */
