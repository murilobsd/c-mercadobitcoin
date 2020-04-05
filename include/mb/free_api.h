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

#ifndef _MBAPI_H
#define _MBAPI_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BIDS_LIMIT 1000
#define ASKS_LIMIT 1000

/* methods name */
#define S_TICKER "ticker"

/*
typedef struct *parameters ParameterPtr;
typedef struct parameter {
	char *name;
	char *value;
} Parameter;
*/

/*
struct ask {
	double price;
	double quantity;
};

struct bid  {
	double price;
	double quantity;
};

struct order_book {
	struct ask	[ASKS_LIMIT]asks;
	struct bid	[BIDS_LIMIT]bids;	

};
*/

typedef struct free_api FreeApi;
typedef struct api_methods {
	//ApiType _type;
	int 	(*ticker)(FreeApi *, CoinType);
	MBError (*get_error)(FreeApi *);
	void	(*get_data)(FreeApi *, void *);
	//void (*orderbook)(FreeApi *, CointType);
	//void (*trades)(FreeApi *, CointType, ParameterPtr);
	//void (*day_summary)(FreeApi *, CointType, ParameterPtr);
} FreeApiMethods;

struct free_api {
	FreeApiMethods *ops;
};

extern FreeApi * freeapi_init(void);
extern void clean_freeapi(FreeApi *);

#ifdef __cplusplus
}
#endif

#endif
