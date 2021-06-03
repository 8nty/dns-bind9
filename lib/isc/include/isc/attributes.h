/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#ifdef _WIN32
#define __attribute__(attribute) /* do nothing */
#else
#define __declspec(modifier) /* do nothing */
#endif

#if HAVE_FUNC_ATTRIBUTE_NORETURN
#define ISC_NORETURN __attribute__((noreturn))
#elif _WIN32
#define ISC_NORETURN __declspec(noreturn)
#else
#define ISC_NORETURN
#endif

#if HAVE_FUNC_ATTRIBUTE_RETURNS_NONNULL
#define ISC_ATTR_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#define ISC_ATTR_RETURNS_NONNULL
#endif

#ifdef HAVE_FUNC_ATTRIBUTE_MALLOC
/*
 * Indicates that a function is malloc-like, i.e., that the
 * pointer P returned by the function cannot alias any other
 * pointer valid when the function returns.
 */
#define ISC_ATTR_MALLOC __attribute__((malloc))
#if HAVE_MALLOC_EXT_ATTR
/*
 * Associates deallocator as a suitable deallocation function
 * for pointers returned from the function marked with the attribute.
 */
#define ISC_ATTR_DEALLOCATOR(deallocator) __attribute__((malloc(deallocator)))
/*
 * Similar to ISC_ATTR_DEALLOCATOR, but allows to speficy an index "idx",
 * which denotes the positional argument to which when the pointer is passed
 * in calls to deallocator has the effect of deallocating it.
 */
#define ISC_ATTR_DEALLOCATOR_IDX(deallocator, idx) \
	__attribute__((malloc(deallocator, idx)))
/*
 * Combines both ISC_ATTR_MALLOC and ISC_ATTR_DEALLOCATOR attributes.
 */
#define ISC_ATTR_MALLOC_DEALLOCATOR(deallocator) \
	__attribute__((malloc, malloc(deallocator)))
/*
 * Similar to ISC_ATTR_MALLOC_DEALLOCATOR, but allows to speficy an index "idx",
 * which denotes the positional argument to which when the pointer is passed
 * in calls to deallocator has the effect of deallocating it.
 */
#define ISC_ATTR_MALLOC_DEALLOCATOR_IDX(deallocator, idx) \
	__attribute__((malloc, malloc(deallocator, idx)))
#else /* #ifdef HAVE_MALLOC_EXT_ATTR */
/*
 * There is support for malloc attribute but not for
 * extended attributes, so macros that combine attribute malloc
 * with a deallocator will only expand to malloc attribute.
 */
#define ISC_ATTR_DEALLOCATOR(deallocator)
#define ISC_ATTR_DEALLOCATOR_IDX(deallocator, idx)
#define ISC_ATTR_MALLOC_DEALLOCATOR(deallocator)	  ISC_ATTR_MALLOC
#define ISC_ATTR_MALLOC_DEALLOCATOR_IDX(deallocator, idx) ISC_ATTR_MALLOC
#endif
#else /* #ifdef HAVE_FUNC_ATTRIBUTE_MALLOC */
/*
 * There is no support for malloc attribute.
 */
#define ISC_ATTR_MALLOC
#define ISC_ATTR_DEALLOCATOR(deallocator)
#define ISC_ATTR_DEALLOCATOR_IDX(deallocator, idx)
#define ISC_ATTR_MALLOC_DEALLOCATOR(deallocator)
#define ISC_ATTR_MALLOC_DEALLOCATOR_IDX(deallocator, idx)
#endif /* HAVE_FUNC_ATTRIBUTE_MALLOC */
