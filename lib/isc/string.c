/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 * SPDX-FileCopyrightText: 1990, 1993 The Regents of the University of
 *                         California.
 *
 * SPDX-License-Identifier: MPL-2.0 AND BSD-3-Clause
 */

/*! \file */

#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#endif /* ifdef _GNU_SOURCE */
#include <string.h>

#include <isc/string.h> /* IWYU pragma: keep */

#if !defined(HAVE_STRLCPY)
size_t
strlcpy(char *dst, const char *src, size_t size) {
	char *d = dst;
	const char *s = src;
	size_t n = size;

	/* Copy as many bytes as will fit */
	if (n != 0U && --n != 0U) {
		do {
			if ((*d++ = *s++) == 0) {
				break;
			}
		} while (--n != 0U);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0U) {
		if (size != 0U) {
			*d = '\0'; /* NUL-terminate dst */
		}
		while (*s++) {
		}
	}

	return (s - src - 1); /* count does not include NUL */
}
#endif /* !defined(HAVE_STRLCPY) */

#if !defined(HAVE_STRLCAT)
size_t
strlcat(char *dst, const char *src, size_t size) {
	char *d = dst;
	const char *s = src;
	size_t n = size;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0U && *d != '\0') {
		d++;
	}
	dlen = d - dst;
	n = size - dlen;

	if (n == 0U) {
		return (dlen + strlen(s));
	}
	while (*s != '\0') {
		if (n != 1U) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return (dlen + (s - src)); /* count does not include NUL */
}
#endif /* !defined(HAVE_STRLCAT) */

int
isc_string_strerror_r(int errnum, char *buf, size_t buflen) {
#if defined(_WIN32) || defined(_WIN64)
	return (strerror_s(buf, buflen, errnum));
#else  /* if defined(_WIN32) || defined(_WIN64) */
	return (strerror_r(errnum, buf, buflen));
#endif /* if defined(_WIN32) || defined(_WIN64) */
}
