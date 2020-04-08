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
#include <string.h>

#include "json.h"
#include "trade.h"

#define MOD_NAME 	"trades"
#define SELF 		((struct trade_t *)t)
#define SELF_S 		((struct trades_t *)ts)
#define DEF_VAL_ERR	0.0
#define MAX_TRADES	1000 /* max api return */

struct trade_t {
	double amount;
	uint64_t date;
	double price;   
	int tid;
	TradeType type;
};

struct trades_t {
        struct trade_t *trades[MAX_TRADES];
        size_t len;
        size_t capacity;
};

/* trade */
static TradePtr         init_trade(void);
static TradePtr         init_trade_fromjson(json_t *);
static void             trade_set_amount(struct trade_t *, double);
static void             trade_set_date(struct trade_t *, uint64_t);
static void             trade_set_price(struct trade_t *, double);
static void             trade_set_tid(struct trade_t *, int);
static void             trade_set_type(struct trade_t *, const char *);

/* trades */
static TradesPtr        init_trades(void);
static bool             trades_isfull(struct trades_t *);
static void             trades_set_capacity(struct trades_t *, size_t);
static void             trades_set_len(struct trades_t *, size_t);
static bool             trades_add_trade(struct trades_t *, struct trade_t *);


size_t
trades_get_size(TradesPtr ts)
{
        if (SELF_S != NULL)
                return SELF_S->len;
        return 0;
}

static bool
trades_add_trade(struct trades_t *ts, struct trade_t *t)
{
        if (!trades_isfull(ts)) {
                ts->trades[ts->len] = t;
                ts->len++;
                return true;
        }
        return false;
}

static void
trades_set_len(struct trades_t *t, size_t len)
{
        if (t != NULL)
                t->len = len;
}

static void
trades_set_capacity(struct trades_t *t, size_t cap)
{
        if (t != NULL)
                t->capacity = cap;
}

static bool
trades_isfull(struct trades_t *t)
{
        if (t->len < t->capacity)
                return false;
        return true;
}

static void
trade_set_type(struct trade_t *t, const char *value)
{
        size_t eq = 0;

        if (t != NULL) {
                if ((eq = strcmp("buy", value)) == 0)
                        t->type = TRADE_BUY;
                else if ((eq = strcmp("sell", value)) == 0)
                        t->type = TRADE_SELL;
                else
                        t->type = TRADE_INVALID;
        }
}

static void
trade_set_tid(struct trade_t *t, int value)
{
        if (t != NULL)
                t->tid = value;
}

static void
trade_set_price(struct trade_t *t, double value)
{
        if (t != NULL)
                t->price = value;
}

static void
trade_set_date(struct trade_t *t, uint64_t value)
{
        if (t != NULL)
                t->date = value;
}

static void
trade_set_amount(struct trade_t *t, double value)
{
        if (t != NULL)
                t->amount = value;
}

static TradePtr
init_trade_fromjson(json_t *node)
{
        TradePtr t = NULL;
        uint64_t date;
        double amount, price;
        int tid;

        if (node == NULL)
                return NULL;

        t = init_trade();

        date = json_get_integer(node, "date");
        amount = json_get_double(node, "amount");
        price = json_get_double(node, "price");
        tid = json_get_integer(node, "tid");
        const char *type = json_get_string(node, "type");

        /* set values */
        trade_set_amount(SELF, amount);
        trade_set_date(SELF, date);
        trade_set_price(SELF, price);
        trade_set_tid(SELF, tid);
        trade_set_type(SELF, type);

        return t;
}

TradesPtr
init_trades_fromjson(const char *datastr)
{
	TradesPtr ts = NULL;
	json_t *root;
        size_t n_trades;
	
	if (datastr == NULL)
		return NULL;

	if ((root = json_parse_str(datastr)) == NULL)
		return NULL;

        n_trades = json_array_size(root);

        if (n_trades > MAX_TRADES) {
                json_free(root);
                return NULL;
        }

	/* init trades object */
	ts = init_trades();

        for (size_t i = 0; i < n_trades; i++) {
                TradePtr t;
                json_t *trade_obj;

                trade_obj = json_array_get(root, i);

                if ((t = init_trade_fromjson(trade_obj)) == NULL)
                        json_free(root);
                else {
                        /* SELF_S struct tradeS_t * 
                         * SELF struct trade_t *
                         */
                        trades_add_trade(SELF_S, SELF);
                }
        }

	/* decrement ref */
	json_free(root);

	return ts;
}

static TradesPtr
init_trades(void)
{
	TradesPtr ts;

	ts = (TradesPtr)malloc(sizeof(struct trades_t));

	if (ts == NULL)
		err(1, NULL);

	/* init values */
	trades_set_capacity(SELF_S, MAX_TRADES);
	trades_set_len(SELF_S, 0);

	return ts;
}

static TradePtr
init_trade(void)
{
	TradePtr t;

	t = (TradePtr)malloc(sizeof(struct trade_t));

	if (t == NULL)
		err(1, NULL);

	return t;
}

void
trade_free(TradePtr *t)
{
	if (t != NULL) {
                free(*t);
                *t = NULL;
        }
}

void
trades_free(TradesPtr ts)
{
	if (ts == NULL)
                return;

        if (SELF_S->len > 0) {
                for (size_t i = 0; i < SELF_S->len; i++)
                        trade_free(&SELF_S->trades[i]);
                SELF_S->len = 0;
        }

        free(ts);
}

const char *
trades_get_modname(void)
{
	return MOD_NAME;
}
