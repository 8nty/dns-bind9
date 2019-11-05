/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

#include <inttypes.h>

#include <isc/align.h>
#include <isc/atomic.h>
#include <isc/queue.h>
#include <isc/string.h>
#include <isc/mem.h>
#include <isc/hp.h>

#define BUFFER_SIZE 1024

#define MAX_THREADS 128

static uintptr_t nulluintptr = (uintptr_t)NULL;

typedef struct node {
	atomic_uint_fast32_t deqidx;
	atomic_uintptr_t items[BUFFER_SIZE];
	atomic_uint_fast32_t enqidx;
	atomic_uintptr_t next;
	isc_mem_t *mctx;
} node_t;

/* we just need one Hazard Pointer */
#define HP_TAIL 0
#define HP_HEAD 0

struct isc_queue {
	alignas(128) atomic_uintptr_t head;
	alignas(128) atomic_uintptr_t tail;
	isc_mem_t *mctx;
	int max_threads;
	int taken;
	isc_hp_t *hp;
};

static node_t *
node_new(isc_mem_t *mctx, uintptr_t item) {
	node_t *node = isc_mem_get(mctx, sizeof(*node));
	*node = (node_t){
		.deqidx = 0,
		.enqidx = 1,
		.next = 0,
		.items = { item, 0 }
	};
	isc_mem_attach(mctx, &node->mctx);
	return (node);
}

static void
node_destroy(void *node0) {
	node_t *node = (node_t *)node0;
	isc_mem_putanddetach(&node->mctx, node, sizeof(*node));
}

static bool
node_cas_next(node_t *node, node_t *cmp, const node_t *val) {
	return (atomic_compare_exchange_strong(&node->next,
					       (uintptr_t *)&cmp,
					       (uintptr_t)val));
}

static bool
queue_cas_tail(isc_queue_t *queue, node_t *cmp, const node_t *val) {
	return (atomic_compare_exchange_strong(&queue->tail,
					       (uintptr_t *)&cmp,
					       (uintptr_t)val));
}

static bool
queue_cas_head(isc_queue_t *queue, node_t *cmp, const node_t *val) {
	return (atomic_compare_exchange_strong(&queue->head,
					       (uintptr_t *)&cmp,
					       (uintptr_t)val));
}

isc_queue_t *
isc_queue_new(isc_mem_t *mctx, int max_threads) {
	isc_queue_t *queue = isc_mem_get(mctx, sizeof(*queue));
	node_t *sentinel = node_new(mctx, nulluintptr);

	if (max_threads == 0) {
		max_threads = MAX_THREADS;
	}

	*queue = (isc_queue_t){
		.max_threads = max_threads,
	};

	isc_mem_attach(mctx, &queue->mctx);

	queue->hp = isc_hp_new(mctx, 1, node_destroy);

	atomic_init(&sentinel->enqidx, 0);
	atomic_init(&queue->head, (uintptr_t)sentinel);
	atomic_init(&queue->tail, (uintptr_t)sentinel);

	return (queue);
}

void
isc_queue_enqueue(isc_queue_t *queue, uintptr_t item) {
	INSIST(item != nulluintptr);

	while (true) {
		node_t *lt = NULL;
		atomic_uint_fast32_t idx;
		uintptr_t n = nulluintptr;

		lt = (node_t *)isc_hp_protect(queue->hp, 0, &queue->tail);
		idx = atomic_fetch_add(&lt->enqidx, 1);
		if (idx > BUFFER_SIZE-1) {
			node_t *lnext = NULL;

			if (lt != (node_t *)atomic_load(&queue->tail)) {
				continue;
			}

			lnext = (node_t *)atomic_load(&lt->next);
			if (lnext == NULL) {
				node_t *newnode = node_new(queue->mctx, item);
				if (node_cas_next(lt, NULL, newnode)) {
					queue_cas_tail(queue, lt, newnode);
					isc_hp_clear(queue->hp);
					return;
				}
				node_destroy(newnode);
			} else {
				queue_cas_tail(queue, lt, lnext);
			}

			continue;
		}

		if (atomic_compare_exchange_strong(&lt->items[idx], &n, item)) {
			isc_hp_clear(queue->hp);
			return;
		}
	}
}

uintptr_t
isc_queue_dequeue(isc_queue_t *queue) {
	while (true) {
		node_t *lh = NULL;
		atomic_uint_fast32_t idx;
		uintptr_t item;

		lh = (node_t *)isc_hp_protect(queue->hp, 0, &queue->head);
		if (atomic_load(&lh->deqidx) >= atomic_load(&lh->enqidx) &&
		    atomic_load(&lh->next) == nulluintptr)
		{
			break;
		}

		idx = atomic_fetch_add(&lh->deqidx, 1);
		if (idx > BUFFER_SIZE-1) {
			node_t *lnext = (node_t *)atomic_load(&lh->next);
			if (lnext == NULL) {
				break;
			}
			if (queue_cas_head(queue, lh, lnext)) {
				isc_hp_retire(queue->hp, (uintptr_t)lh);
			}

			continue;
		}

		item = atomic_exchange(&(lh->items[idx]),
				       (uintptr_t)&queue->taken);
		if (item == nulluintptr) {
			continue;
		}

		isc_hp_clear(queue->hp);
		return (item);
	}

	isc_hp_clear(queue->hp);
	return (nulluintptr);
}

void
isc_queue_destroy(isc_queue_t *queue) {
	node_t *last;

	while (isc_queue_dequeue(queue) != nulluintptr) {
		/* do nothing */
	}

	last = (node_t *)atomic_load_relaxed(&queue->head);
	node_destroy(last);
	isc_hp_destroy(queue->hp);
	isc_mem_putanddetach(&queue->mctx, queue, sizeof(*queue));
}
