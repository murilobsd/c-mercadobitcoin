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

#include "mb.h"

const char * const MB_ERROR_STRS[] = 
{
    	"MBE_OK",
    	"MBE_NOMEM",
    	"MBE_TIMEOUT",
    	"MBE_NOT_FOUND_COIN",
    	"MBE_NOT_FOUND_METHOD",
};

const char * 
mb_error_str(MBError err)
{
    const char* err_str = NULL;

    if (err >= MBE_COUNT) {
        goto done;
    }

    err_str = MB_ERROR_STRS[err];

done:
    return err_str;
}

