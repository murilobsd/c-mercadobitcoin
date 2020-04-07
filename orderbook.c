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
#include <stdio.h>

#include "json.h"
#include "orderbook.h"

#define MOD_NAME 	"orderbook"
#define SELF 		((struct orderbook_t *)ob)
#define DEF_VAL_ERR	0.0
#define MAX_ORDERS	1000 /* max api return */

struct orderbook_t {
	OrderPtr asks[MAX_ORDERS];
	OrderPtr bids[MAX_ORDERS];
	size_t len_asks;
	size_t len_bids;
	size_t capacity;
};

static OrderBookPtr 	init_orderbook(void);
static void		orderbook_set_date(struct orderbook_t *, uint64_t);
static void		orderbook_set_capacity(struct orderbook_t *, size_t);
static void		orderbook_add_ask(struct orderbook_t *, OrderPtr);
static void		orderbook_add_bid(struct orderbook_t *, OrderPtr);
static bool 	        orderbook_isfull(struct orderbook_t *);
static void		orderbook_add(struct orderbook_t *, OrderPtr);

static void
orderbook_add_order(struct orderbook_t *ob, OrderPtr or)
{
        OrderType or_t;

        if(!orderbook_isfull(ob)) {
                or_t = order_get_type(or);
                switch(or_t) {
                case OR_ASK:
                        orderbook_add_ask(ob, or);
                        break;
                case OR_BID:
                        orderbook_add_bid(ob, or);
                        break;
                default:
                        warn("invalid order type: %d", or_t);
                        break;
                }
        }
}
 
/*
 * TODO: fix checking lenght based on order type
 */
static bool
orderbook_isfull(struct orderbook_t *ob)
{
	return	(ob->len_asks < ob->capacity ) ? false : true;
}

static void
orderbook_add_ask(struct orderbook_t *ob, OrderPtr or)
{
        if(!orderbook_isfull(ob)) {
                ob->asks[ob->len_asks] = or;
                ob->len_asks++;
        }
}

static void
orderbook_add_bid(struct orderbook_t *ob, OrderPtr or)
{
        if(!orderbook_isfull(ob)) {
                ob->bids[ob->len_bids] = or;
                ob->len_bids++;
        }
}

static void
orderbook_set_capacity(struct orderbook_t *ob, size_t cap)
{
	if (ob != NULL)
		ob->capacity = cap;
}

static void
orderbook_set_len(struct orderbook_t *ob, size_t len)
{
	if (ob != NULL) {
		ob->len_asks = len;
		ob->len_bids = len;
        }
}

OrderBookPtr
init_orderbook_fromjson(const char *datastr)
{
	OrderBookPtr ob = NULL;
	json_t *root, *node_asks, *node_bids;
        size_t n_asks, n_bids, i;
	
	if (datastr == NULL)
		return NULL;

	if ((root = json_parse_str(datastr)) == NULL)
		return NULL;
        
        /* TODO: criar um metodo no modulo order para gerar um const char *
         * baseado no tipo de oferta, ex: retorna "asks"
         */
	if ((node_asks = json_get_array(root, "asks", &n_asks)) == NULL) {
		json_free(root);
		return NULL;
	}

	if ((node_bids = json_get_array(root, "bids", &n_bids)) == NULL) {
		json_free(root);
		return NULL;
	}
        
        /* nao temos nenhum elemento */
        if (n_asks <= 0 || n_bids <= 0) {
                json_free(root);
                return NULL;
        }

	/* init orderbook object */
	ob = init_orderbook();

        for (i = 0; i < n_asks; i++) {
                double price, qtd;
                size_t s_order; /* size order  == 2*/
                json_t *order_arr;
                OrderPtr or;

                order_arr = json_array_get(node_asks, i);
                /* melhorar isso */
                if (!json_is_array(order_arr)) {
                        json_free(root);
                        orderbook_free(ob);
                        return NULL;
                }
                s_order = json_array_size(order_arr);
                if (s_order != 2) {
                        json_free(root);
                        orderbook_free(ob);
                        return NULL;
                }
                //printf("Asks size: %lu\n", s_order);
                price = json_get_array_double(order_arr, 0);
                qtd = json_get_array_double(order_arr, 1);
                or = init_order(OR_ASK, price, qtd);
                orderbook_add_order(SELF, or);
        }

        for (i = 0; i < n_asks; i++) {
                double price, qtd;
                size_t s_order; /* size order  == 2*/
                json_t *order_arr;
                OrderPtr or;

                order_arr = json_array_get(node_bids, i);
                /* melhorar isso */
                if (!json_is_array(order_arr)) {
                        json_free(root);
                        orderbook_free(ob);
                        return NULL;
                }
                s_order = json_array_size(order_arr);
                if (s_order != 2) {
                        json_free(root);
                        orderbook_free(ob);
                        return NULL;
                }
                price = json_get_array_double(order_arr, 0);
                qtd = json_get_array_double(order_arr, 1);
                or = init_order(OR_BID, price, qtd);
                orderbook_add_order(SELF, or);
        }

	/* decrement ref */
	json_free(root);

	return ob;
}

static OrderBookPtr
init_orderbook(void)
{
	OrderBookPtr ob;

	ob = (OrderBookPtr)malloc(sizeof(struct orderbook_t));

	if (ob == NULL)
		err(1, NULL);

	/* init values */
	orderbook_set_capacity(SELF, MAX_ORDERS);
	orderbook_set_len(SELF, 0);

	return ob;
}

void
orderbook_free(OrderBookPtr ob)
{
	if (ob == NULL)
                return;

        if (SELF->len_asks > 0) {
                for (size_t i = 0; i < SELF->len_asks; i++)
                        order_free(&SELF->asks[i]);
                SELF->len_asks = 0;
        }

        if (SELF->len_bids > 0) {
                for (size_t i = 0; i < SELF->len_bids; i++)
                        order_free(&SELF->bids[i]);
                SELF->len_bids= 0;
        }

        free(ob);
}

const char *
orderbook_get_modname(void)
{
	return MOD_NAME;
}
