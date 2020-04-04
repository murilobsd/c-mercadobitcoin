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

#ifndef _MBHTTP_H
#define _MBHTTP_H

#define BASE_URL 	"https://www.mercadobitcoin.net/api"
#define USERAGENT	"cmb/0.1"
#define TIMEOUT_CON	2	// timeout connection
#define TIMEOUT		60 	// timeout 60 seconds

/* methods http */
typedef enum {
	GET,
	POST
} HttpMethod;


typedef struct pkt Req; /* request */
typedef struct pkt Resp; /* response */
struct pkt {
	char *data;
	char *offset;
	size_t size;	
	long status_code;
};

void http_get(const char *, Resp *);

#endif /* _MBHTTP_H */
