/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

#pragma once

#if !defined(HAVE_JEMALLOC)

#include <isc/util.h>

const char *malloc_conf = NULL;

#if defined(HAVE_MALLOC_SIZE) || defined(HAVE_MALLOC_USABLE_SIZE)

#include <stdlib.h>

static inline void *
mallocx(size_t size, int flags) {
	UNUSED(flags);
	void *__ptr = malloc(size);
	REQUIRE(__ptr != NULL);
	return (__ptr);
}

static inline void
sdallocx(void *ptr, size_t size, int flags) {
	UNUSED(size);
	UNUSED(flags);

	free(ptr);
}

static inline void *
rallocx(void *ptr, size_t size, int flags) {
	UNUSED(flags);
	REQUIRE(size != 0);

	void *__ptr = realloc(ptr, size);
	REQUIRE(__ptr != NULL);

	return (__ptr);
}

#ifdef HAVE_MALLOC_SIZE

#include <malloc/malloc.h>

static inline size_t
sallocx(void *ptr, int flags) {
	UNUSED(flags);

	return (malloc_size(ptr));
}

#elif HAVE_MALLOC_USABLE_SIZE

#include <malloc.h>

static inline size_t
sallocx(void *ptr, int flags) {
	UNUSED(flags);

	return (malloc_usable_size(ptr));
}

#endif /* HAVE_MALLOC_SIZE */

#else /* defined(HAVE_MALLOC_SIZE) || defined (HAVE_MALLOC_USABLE_SIZE) */

#include <stdlib.h>

static inline void *
mallocx(size_t size, int flags) {
	UNUSED(flags);

	size_t *__ptr = malloc(size + sizeof(size_t));
	REQUIRE(__ptr != NULL);
	__ptr[0] = size;

	return (&__ptr[1]);
}

static inline void
sdallocx(void *ptr, size_t size, int flags) {
	UNUSED(size);
	UNUSED(flags);

	free(&((size_t *)ptr)[-1]);
}

static inline size_t
sallocx(void *ptr, int flags) {
	UNUSED(flags);

	return (((size_t *)ptr)[-1]);
}

static inline void *
rallocx(void *ptr, size_t size, int flags) {
	UNUSED(flags);

	size_t *__ptr = realloc(&((size_t *)ptr)[-1], size);
	REQUIRE(__ptr != NULL);
	__ptr[0] = size;

	return (&__ptr[1]);
}

#endif /* defined(HAVE_MALLOC_SIZE) || defined (HAVE_MALLOC_USABLE_SIZE) */

#endif /* !defined(HAVE_JEMALLOC) */
