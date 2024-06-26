#ifndef BEARSSL_IMPL_SSL_PRF_MD5SHA1_HPP
#define BEARSSL_IMPL_SSL_PRF_MD5SHA1_HPP

/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "inner.h"

/* see bearssl.h */
 inline void
br_tls10_prf(void *dst, size_t len,
	const void *secret, size_t secret_len,
	const char *label, const void *seed, size_t seed_len)
{
	const unsigned char *s1;
	size_t slen;

	s1 = (unsigned char *)secret;
	slen = (secret_len + 1) >> 1;
	memset(dst, 0, len);
	br_tls_phash(dst, len, &br_md5_vtable,
		s1, slen, label, seed, seed_len);
	br_tls_phash(dst, len, &br_sha1_vtable,
		s1 + secret_len - slen, slen, label, seed, seed_len);
}
#endif
