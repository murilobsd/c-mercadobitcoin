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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "mb/http.h"
#include "mb/utils.h"

static size_t 	recv_data_cb(char *, size_t, size_t, void *);
static MBError request(const char *, HttpMethod, Resp *);

MBError
http_get(const char *url, Resp *resp) {
	MBError err = MBE_OK;
	err = request(url, GET, resp);
	return err;
}

static MBError 
request(const char *url, HttpMethod meth, Resp *resp)
{
	CURL *curl = NULL;
	CURLcode curl_code;
	MBError err = MBE_OK;

	/* init curl */
	curl = curl_easy_init();
	

	if (curl != NULL) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USERAGENT);
#ifdef DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
		/* FIX: dynamic options to timeout */
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, TIMEOUT_CON);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, TIMEOUT);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, recv_data_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)resp);
		
		// execute
		curl_code = curl_easy_perform(curl);

		// error curl
		if (curl_code != CURLE_OK) {
			debug("curl error ex: %s\n",
			curl_easy_strerror(curl_code));
			err = MBE_CURL_CODE;
		} else {
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,
			&resp->status_code);
		}
		
		// error api
		if (resp->status_code != 200) {
			debug("status code error %ld\n", resp->status_code);
			err = MBE_HTTP_API;
		}
		// clean curl
		curl_easy_cleanup(curl);
	} else {
		debug("failed alloc curl\n");
		err = MBE_NOMEM;
	}

	return err;
}

static size_t
recv_data_cb(char *ptr, size_t size, size_t nmemb, void *data)
{
	size_t ptrsize = nmemb*size;
	Req *pr = (Req *)data;

	pr->data = (char *)realloc(pr->data, pr->size + ptrsize + 1);

	if (pr->data) {
		memcpy(&(pr->data[pr->size]), ptr, ptrsize);
		pr->size += ptrsize;
		pr->data[pr->size] = '\0';
	}
	else {
		fprintf(stderr, "ops: resp realloc failed\n");
	}

	return ptrsize;
}


