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

#ifndef _MERCADOBITCOIN_H
#define _MERCADOBITCOIN_H

#include <curl/curl.h>

#define FREE_API_URL 	"https://www.mercadobitcoin.net/api/%s/%s/"
#define USERAGENT	"cmb/0.1"
#define TIMEOUT_CON	2	// timeout connection
#define TIMEOUT		60 	// timeout 60 seconds

/* errors */
typedef enum mb_error_e {
	// All fine
	MBE_OK,

	// Failed alloc memory
	MBE_NOMEM,

	// Timeout connection or handshake
	MBE_TIMEOUT,

	// Error count *always keep last*
	MBE_COUNT,
} mb_error_t;

/* coins */
typedef enum coin_t CoinType;
enum coin_t {
	BTC,	/* Bitcoin */
	LTC,	/* Litecoint */
	BCH,	/* BCash */
	XRP,	/* XRP (Ripple */
	ETH	/* Ethereum */
};

/* methods http */
enum http_method {
	GET
};

typedef struct pkt FreeReq;
typedef struct pkt FreeResp;
struct pkt {
	char *data;
	char *offset;
	size_t size;	
};

typedef struct free_api_t FreeApi;
struct free_api_t {
	enum http_method 	http_meth;
	char 			*url;		/* url request*/	
	CURLcode		curl_code;	/* http status code */
	FreeReq			req;		/* data request */
	FreeResp		resp;		/* data response */
	long			status_code;

	/* methods */
	void (*ticker)(FreeApi *, CoinType);
};

/* mb.c */
extern FreeApi 		*free_api_init(void);
extern void	 	 free_api_clean(FreeApi *);

/* errors.c */
extern const char	*mb_error_str(mb_error_t err);


/* misc */
#if DEBUG
#define debug(fmt, ...) \
        do { fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
         __LINE__, __func__, ##__VA_ARGS__); } while (0)
#else
#define debug(fmt, ...) do {} while(0)
#endif

#endif /* _MERCADOBITCOIN_H */
