/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DLZ_PTHREAD_H
#define DLZ_PTHREAD_H 1

#ifndef PTHREADS
#define PTHREADS 1
#endif /* ifndef PTHREADS */

#ifdef PTHREADS
#include <pthread.h>
#define dlz_mutex_t	  pthread_mutex_t
#define dlz_mutex_init	  pthread_mutex_init
#define dlz_mutex_destroy pthread_mutex_destroy
#define dlz_mutex_lock	  pthread_mutex_lock
#define dlz_mutex_trylock pthread_mutex_trylock
#define dlz_mutex_unlock  pthread_mutex_unlock
#else /* !PTHREADS */
#define dlz_mutex_t	     void
#define dlz_mutex_init(a, b) (0)
#define dlz_mutex_destroy(a) (0)
#define dlz_mutex_lock(a)    (0)
#define dlz_mutex_trylock(a) (0)
#define dlz_mutex_unlock(a)  (0)
#endif /* ifdef PTHREADS */

#endif /* DLZ_PTHREAD_H */
