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

#ifndef _MBTYPES_H
#define _MBTYPES_H

/* api types */
typedef enum api_t {
	FREE,
	TRADE,
} ApiType;

/* coin */
typedef enum coin_t {
	BTC,	/* Bitcoin */
	LTC,	/* Litecoint */
	BCH,	/* BCash */
	XRP,	/* XRP (Ripple */
	ETH	/* Ethereum */
} CoinType;

/* ticker data */
typedef struct {
	double high;
	double low;
	double vol;
	double last;
	double buy;
	double sell;
	uint64_t date;
	
} Ticker;


typedef enum data_t {
	TICKER, /* ticker struct */
} DataType;

/* errors */
typedef enum mb_error_e {
	// All fine
	MBE_OK = 0,

	// Failed alloc memory
	MBE_NOMEM,

	// Timeout connection or handshake
	MBE_TIMEOUT,
	
	// Not found coin
	MBE_NOT_FOUND_COIN,

	// Not found method
	MBE_NOT_FOUND_METHOD,

	// Error count *always keep last*
	MBE_COUNT,
} MBError;

/* mercado bitcoin data */
typedef struct {
	DataType _type;
	union {
		Ticker *ticker;
	} data;
	size_t size;
	MBError error;
} MBData;


#endif
