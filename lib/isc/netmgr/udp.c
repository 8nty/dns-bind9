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

#include <unistd.h>
#include <uv.h>

#include <isc/atomic.h>
#include <isc/buffer.h>
#include <isc/condition.h>
#include <isc/magic.h>
#include <isc/mem.h>
#include <isc/netmgr.h>
#include <isc/random.h>
#include <isc/refcount.h>
#include <isc/region.h>
#include <isc/result.h>
#include <isc/sockaddr.h>
#include <isc/thread.h>
#include <isc/util.h>

#include "netmgr-int.h"
#include "uv-compat.h"

static isc_result_t
udp_send_direct(isc_nmsocket_t *sock, isc__nm_uvreq_t *req,
		isc_sockaddr_t *peer);

static void
udp_recv_cb(uv_udp_t *handle, ssize_t nrecv, const uv_buf_t *buf,
	    const struct sockaddr *addr, unsigned flags);

static void
udp_send_cb(uv_udp_send_t *req, int status);

static void
udp_close_cb(uv_handle_t *uvhandle);

isc_result_t
isc_nm_listenudp(isc_nm_t *mgr, isc_nmiface_t *iface, isc_nm_recv_cb_t cb,
		 void *cbarg, size_t extrahandlesize, isc_nmsocket_t **sockp) {
	isc_nmsocket_t *nsock = NULL;

	REQUIRE(VALID_NM(mgr));

	/*
	 * We are creating mgr->nworkers duplicated sockets, one
	 * socket for each worker thread.
	 */
	nsock = isc_mem_get(mgr->mctx, sizeof(isc_nmsocket_t));
	isc__nmsocket_init(nsock, mgr, isc_nm_udplistener, iface);
	nsock->nchildren = mgr->nworkers;
	atomic_init(&nsock->rchildren, mgr->nworkers);
	nsock->children = isc_mem_get(mgr->mctx,
				      mgr->nworkers * sizeof(*nsock));
	memset(nsock->children, 0, mgr->nworkers * sizeof(*nsock));

	INSIST(nsock->rcb.recv == NULL && nsock->rcbarg == NULL);
	nsock->rcb.recv = cb;
	nsock->rcbarg = cbarg;
	nsock->extrahandlesize = extrahandlesize;

	for (size_t i = 0; i < mgr->nworkers; i++) {
		uint16_t family = iface->addr.type.sa.sa_family;
		int res = 0;

		isc__netievent_udplisten_t *ievent = NULL;
		isc_nmsocket_t *csock = &nsock->children[i];

		isc__nmsocket_init(csock, mgr, isc_nm_udpsocket, iface);
		csock->parent = nsock;
		csock->tid = i;
		csock->extrahandlesize = extrahandlesize;

		INSIST(csock->rcb.recv == NULL && csock->rcbarg == NULL);
		csock->rcb.recv = cb;
		csock->rcbarg = cbarg;
		csock->fd = socket(family, SOCK_DGRAM, 0);
		RUNTIME_CHECK(csock->fd >= 0);

		/*
		 * This is SO_REUSE**** hell:
		 *
		 * Generally, the SO_REUSEADDR socket option allows reuse of
		 * local addresses.  On Windows, it also allows a socket to
		 * forcibly bind to a port in use by another socket.
		 *
		 * On Linux, SO_REUSEPORT socket option allows sockets to be
		 * bound to an identical socket address. For UDP sockets, the
		 * use of this option can provide better distribution of
		 * incoming datagrams to multiple processes (or threads) as
		 * compared to the traditional technique of having multiple
		 * processes compete to receive datagrams on the same socket.
		 *
		 * On FreeBSD, the same thing is achieved with SO_REUSEPORT_LB.
		 *
		 */
#if defined(SO_REUSEADDR)
		res = setsockopt(csock->fd, SOL_SOCKET, SO_REUSEADDR,
				 &(int){ 1 }, sizeof(int));
		RUNTIME_CHECK(res == 0);
#endif
#if defined(SO_REUSEPORT_LB)
		res = setsockopt(csock->fd, SOL_SOCKET, SO_REUSEPORT_LB,
				 &(int){ 1 }, sizeof(int));
		RUNTIME_CHECK(res == 0);
#elif defined(SO_REUSEPORT)
		res = setsockopt(csock->fd, SOL_SOCKET, SO_REUSEPORT,
				 &(int){ 1 }, sizeof(int));
		RUNTIME_CHECK(res == 0);
#endif

#ifdef SO_INCOMING_CPU
		/* We don't check for the result, because SO_INCOMING_CPU can be
		 * available without the setter on Linux kernel version 4.4, and
		 * setting SO_INCOMING_CPU is just an optimization.
		 */
		(void)setsockopt(csock->fd, SOL_SOCKET, SO_INCOMING_CPU,
				 &(int){ 1 }, sizeof(int));
#endif
		ievent = isc__nm_get_ievent(mgr, netievent_udplisten);
		ievent->sock = csock;
		isc__nm_enqueue_ievent(&mgr->workers[i],
				       (isc__netievent_t *)ievent);
	}

	*sockp = nsock;
	return (ISC_R_SUCCESS);
}

/*%<
 * Allocator for UDP recv operations. Limited to size 20 * (2^16 + 2),
 * which allows enough space for recvmmsg() to get multiple messages at
 * a time.
 *
 * Note this doesn't actually allocate anything, it just assigns the
 * worker's receive buffer to a socket, and marks it as "in use".
 */
static void
udp_alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf) {
	isc_nmsocket_t *sock = uv_handle_get_data(handle);
	isc__networker_t *worker = NULL;

	REQUIRE(VALID_NMSOCK(sock));
	REQUIRE(sock->type == isc_nm_udpsocket);
	REQUIRE(isc__nm_in_netthread());
	REQUIRE(size <= ISC_NETMGR_RECVBUF_SIZE);

	worker = &sock->mgr->workers[sock->tid];
	INSIST(!worker->recvbuf_inuse);

	buf->base = worker->recvbuf;
	buf->len = ISC_NETMGR_RECVBUF_SIZE;
	worker->recvbuf_inuse = true;
}

/*
 * handle 'udplisten' async call - start listening on a socket.
 */
void
isc__nm_async_udplisten(isc__networker_t *worker, isc__netievent_t *ev0) {
	isc__netievent_udplisten_t *ievent = (isc__netievent_udplisten_t *)ev0;
	isc_nmsocket_t *sock = ievent->sock;
	int r, uv_bind_flags = 0;
	int uv_init_flags = 0;

	REQUIRE(sock->type == isc_nm_udpsocket);
	REQUIRE(sock->iface != NULL);
	REQUIRE(sock->parent != NULL);
	REQUIRE(sock->tid == isc_nm_tid());

#ifdef UV_UDP_RECVMMSG
	uv_init_flags |= UV_UDP_RECVMMSG;
#endif
	uv_udp_init_ex(&worker->loop, &sock->uv_handle.udp, uv_init_flags);
	uv_handle_set_data(&sock->uv_handle.handle, NULL);
	isc__nmsocket_attach(sock,
			     (isc_nmsocket_t **)&sock->uv_handle.udp.data);

	r = uv_udp_open(&sock->uv_handle.udp, sock->fd);
	if (r == 0) {
		isc__nm_incstats(sock->mgr, sock->statsindex[STATID_OPEN]);
	} else {
		isc__nm_incstats(sock->mgr, sock->statsindex[STATID_OPENFAIL]);
	}

	if (sock->iface->addr.type.sa.sa_family == AF_INET6) {
		uv_bind_flags |= UV_UDP_IPV6ONLY;
	}

	r = uv_udp_bind(&sock->uv_handle.udp,
			&sock->parent->iface->addr.type.sa, uv_bind_flags);
	if (r == UV_EADDRNOTAVAIL &&
	    isc__nm_socket_freebind(&sock->uv_handle.handle) == ISC_R_SUCCESS)
	{
		/*
		 * Retry binding with IP_FREEBIND (or equivalent option) if the
		 * address is not available. This helps with IPv6 tentative
		 * addresses which are reported by the route socket, although
		 * named is not yet able to properly bind to them.
		 */
		r = uv_udp_bind(&sock->uv_handle.udp,
				&sock->parent->iface->addr.type.sa,
				uv_bind_flags);
	}

	if (r < 0) {
		isc__nm_incstats(sock->mgr, sock->statsindex[STATID_BINDFAIL]);
	}
#ifdef ISC_RECV_BUFFER_SIZE
	uv_recv_buffer_size(&sock->uv_handle.handle,
			    &(int){ ISC_RECV_BUFFER_SIZE });
#endif
#ifdef ISC_SEND_BUFFER_SIZE
	uv_send_buffer_size(&sock->uv_handle.handle,
			    &(int){ ISC_SEND_BUFFER_SIZE });
#endif
	uv_udp_recv_start(&sock->uv_handle.udp, udp_alloc_cb, udp_recv_cb);
}

static void
udp_stop_cb(uv_handle_t *handle) {
	isc_nmsocket_t *sock = uv_handle_get_data(handle);
	atomic_store(&sock->closed, true);

	isc__nmsocket_detach((isc_nmsocket_t **)&sock->uv_handle.udp.data);
}

static void
stop_udp_child(isc_nmsocket_t *sock) {
	REQUIRE(sock->type == isc_nm_udpsocket);
	REQUIRE(sock->tid == isc_nm_tid());

	uv_udp_recv_stop(&sock->uv_handle.udp);
	uv_close((uv_handle_t *)&sock->uv_handle.udp, udp_stop_cb);

	isc__nm_incstats(sock->mgr, sock->statsindex[STATID_CLOSE]);

	LOCK(&sock->parent->lock);
	atomic_fetch_sub(&sock->parent->rchildren, 1);
	UNLOCK(&sock->parent->lock);
	BROADCAST(&sock->parent->cond);
}

static void
stoplistening(isc_nmsocket_t *sock) {
	REQUIRE(sock->type == isc_nm_udplistener);

	for (int i = 0; i < sock->nchildren; i++) {
		isc__netievent_udpstop_t *event = NULL;

		if (isc_nm_tid() == sock->children[i].tid) {
			stop_udp_child(&sock->children[i]);
			continue;
		}

		event = isc__nm_get_ievent(sock->mgr, netievent_udpstop);
		event->sock = &sock->children[i];
		isc__nm_enqueue_ievent(&sock->mgr->workers[i],
				       (isc__netievent_t *)event);
	}

	LOCK(&sock->lock);
	while (atomic_load_relaxed(&sock->rchildren) > 0) {
		WAIT(&sock->cond, &sock->lock);
	}
	atomic_store(&sock->closed, true);
	UNLOCK(&sock->lock);

	isc__nmsocket_prep_destroy(sock);
}

void
isc__nm_udp_stoplistening(isc_nmsocket_t *sock) {
	isc__netievent_udpstop_t *ievent = NULL;

	/* We can't be launched from network thread, we'd deadlock */
	REQUIRE(!isc__nm_in_netthread());
	REQUIRE(VALID_NMSOCK(sock));
	REQUIRE(sock->type == isc_nm_udplistener);

	/*
	 * Socket is already closing; there's nothing to do.
	 */
	if (!isc__nmsocket_active(sock)) {
		return;
	}
	/*
	 * Mark it inactive now so that all sends will be ignored
	 * and we won't try to stop listening again.
	 */
	atomic_store(&sock->active, false);

	/*
	 * If the manager is interlocked, re-enqueue this as an asynchronous
	 * event. Otherwise, go ahead and stop listening right away.
	 */
	if (!isc__nm_acquire_interlocked(sock->mgr)) {
		ievent = isc__nm_get_ievent(sock->mgr, netievent_udpstop);
		ievent->sock = sock;
		isc__nm_enqueue_ievent(&sock->mgr->workers[sock->tid],
				       (isc__netievent_t *)ievent);
	} else {
		stoplistening(sock);
		isc__nm_drop_interlocked(sock->mgr);
	}
}

/*
 * handle 'udpstop' async call - stop listening on a socket.
 */
void
isc__nm_async_udpstop(isc__networker_t *worker, isc__netievent_t *ev0) {
	isc__netievent_udpstop_t *ievent = (isc__netievent_udpstop_t *)ev0;
	isc_nmsocket_t *sock = ievent->sock;

	REQUIRE(sock->iface != NULL);
	UNUSED(worker);

	/*
	 * If this is a child socket, stop listening and return.
	 */
	if (sock->parent != NULL) {
		stop_udp_child(sock);
		return;
	}

	/*
	 * If network manager is paused, re-enqueue the event for later.
	 */
	if (!isc__nm_acquire_interlocked(sock->mgr)) {
		isc__netievent_udplisten_t *event = NULL;

		event = isc__nm_get_ievent(sock->mgr, netievent_udpstop);
		event->sock = sock;
		isc__nm_enqueue_ievent(&sock->mgr->workers[sock->tid],
				       (isc__netievent_t *)event);
	} else {
		stoplistening(sock);
		isc__nm_drop_interlocked(sock->mgr);
	}
}

/*
 * udp_recv_cb handles incoming UDP packet from uv.  The buffer here is
 * reused for a series of packets, so we need to allocate a new one. This
 * new one can be reused to send the response then.
 */
static void
udp_recv_cb(uv_udp_t *handle, ssize_t nrecv, const uv_buf_t *buf,
	    const struct sockaddr *addr, unsigned flags) {
	isc_result_t result;
	isc_nmhandle_t *nmhandle = NULL;
	isc_sockaddr_t sockaddr;
	isc_nmsocket_t *sock = NULL;
	isc_region_t region;
	uint32_t maxudp;
	bool free_buf = true;

	/*
	 * Even though destruction of the socket can only happen from the
	 * network thread that we're in, we still attach to the socket here
	 * to ensure it won't be destroyed by the recv callback.
	 */
	isc__nmsocket_attach(uv_handle_get_data((uv_handle_t *)handle), &sock);

#ifdef UV_UDP_MMSG_CHUNK
	free_buf = ((flags & UV_UDP_MMSG_CHUNK) == 0);
#else
	UNUSED(flags);
#endif

	/*
	 * Three reasons to return now without processing:
	 * - If addr == NULL that's the end of stream - we can
	 *   free the buffer and bail.
	 * - If we're simulating a firewall blocking UDP packets
	 *   bigger than 'maxudp' bytes for testing purposes.
	 * - If the socket is no longer active.
	 */
	maxudp = atomic_load(&sock->mgr->maxudp);
	if ((addr == NULL) || (maxudp != 0 && (uint32_t)nrecv > maxudp) ||
	    (!isc__nmsocket_active(sock)))
	{
		if (free_buf) {
			isc__nm_free_uvbuf(sock, buf);
		}
		isc__nmsocket_detach(&sock);
		return;
	}

	result = isc_sockaddr_fromsockaddr(&sockaddr, addr);
	RUNTIME_CHECK(result == ISC_R_SUCCESS);
	if (!sock->connected) {
		nmhandle = isc__nmhandle_get(sock, &sockaddr, NULL);
	} else {
		nmhandle = sock->statichandle;
	}
	region.base = (unsigned char *)buf->base;
	region.length = nrecv;

	INSIST(sock->rcb.recv != NULL);
	sock->rcb.recv(nmhandle, ISC_R_SUCCESS, &region, sock->rcbarg);
	if (free_buf) {
		isc__nm_free_uvbuf(sock, buf);
	}

	/*
	 * The sock is now attached to the handle, we can detach our ref.
	 */
	isc__nmsocket_detach(&sock);

	/*
	 * If the recv callback wants to hold on to the handle,
	 * it needs to attach to it.
	 */
	isc_nmhandle_unref(nmhandle);
}

/*
 * isc__nm_udp_send sends buf to a peer on a socket.
 * It tries to find a proper sibling/child socket so that we won't have
 * to jump to another thread.
 */
isc_result_t
isc__nm_udp_send(isc_nmhandle_t *handle, isc_region_t *region, isc_nm_cb_t cb,
		 void *cbarg) {
	isc_nmsocket_t *sock = handle->sock;
	isc_nmsocket_t *psock = NULL, *rsock = sock;
	isc_sockaddr_t *peer = &handle->peer;
	isc__netievent_udpsend_t *ievent = NULL;
	isc__nm_uvreq_t *uvreq = NULL;
	uint32_t maxudp = atomic_load(&sock->mgr->maxudp);
	int ntid;

	/*
	 * We're simulating a firewall blocking UDP packets bigger than
	 * 'maxudp' bytes, for testing purposes.
	 *
	 * The client would ordinarily have unreferenced the handle
	 * in the callback, but that won't happen in this case, so
	 * we need to do so here.
	 */
	if (maxudp != 0 && region->length > maxudp) {
		isc_nmhandle_unref(handle);
		return (ISC_R_SUCCESS);
	}

	if (sock->type == isc_nm_udpsocket && !sock->client) {
		INSIST(sock->parent != NULL);
		psock = sock->parent;
	} else if (sock->type == isc_nm_udplistener) {
		psock = sock;
	} else if (!sock->client) {
		INSIST(0);
		ISC_UNREACHABLE();
	}

	if (!isc__nmsocket_active(sock)) {
		return (ISC_R_CANCELED);
	}

	/*
	 * If we're in the network thread, we can send directly.  If the
	 * handle is associated with a UDP socket, we can reuse its thread
	 * (assuming CPU affinity). Otherwise, pick a thread at random.
	 */
	if (isc__nm_in_netthread()) {
		ntid = isc_nm_tid();
	} else if (sock->type == isc_nm_udpsocket && !sock->client) {
		ntid = sock->tid;
	} else {
		ntid = (int)isc_random_uniform(sock->nchildren);
	}

	if (psock != NULL) {
		rsock = &psock->children[ntid];
	}

	uvreq = isc__nm_uvreq_get(sock->mgr, sock);
	uvreq->uvbuf.base = (char *)region->base;
	uvreq->uvbuf.len = region->length;

	uvreq->handle = handle;
	isc_nmhandle_ref(uvreq->handle);

	uvreq->cb.send = cb;
	uvreq->cbarg = cbarg;

	if (isc_nm_tid() == rsock->tid) {
		/*
		 * If we're in the same thread as the socket we can send the
		 * data directly
		 */
		return (udp_send_direct(rsock, uvreq, peer));
	} else {
		/*
		 * We need to create an event and pass it using async channel
		 */
		ievent = isc__nm_get_ievent(sock->mgr, netievent_udpsend);
		ievent->sock = rsock;
		ievent->peer = *peer;
		ievent->req = uvreq;

		isc__nm_enqueue_ievent(&sock->mgr->workers[rsock->tid],
				       (isc__netievent_t *)ievent);
		return (ISC_R_SUCCESS);
	}
}

/*
 * handle 'udpsend' async event - send a packet on the socket
 */
void
isc__nm_async_udpsend(isc__networker_t *worker, isc__netievent_t *ev0) {
	isc__netievent_udpsend_t *ievent = (isc__netievent_udpsend_t *)ev0;

	REQUIRE(worker->id == ievent->sock->tid);

	if (isc__nmsocket_active(ievent->sock)) {
		udp_send_direct(ievent->sock, ievent->req, &ievent->peer);
	} else {
		ievent->req->cb.send(ievent->req->handle, ISC_R_CANCELED,
				     ievent->req->cbarg);
		isc__nm_uvreq_put(&ievent->req, ievent->req->sock);
	}
}

/*
 * udp_send_cb - callback
 */
static void
udp_send_cb(uv_udp_send_t *req, int status) {
	isc_result_t result = ISC_R_SUCCESS;
	isc__nm_uvreq_t *uvreq = (isc__nm_uvreq_t *)req->data;

	REQUIRE(VALID_UVREQ(uvreq));
	REQUIRE(VALID_NMHANDLE(uvreq->handle));

	if (status < 0) {
		result = isc__nm_uverr2result(status);
		isc__nm_incstats(uvreq->sock->mgr,
				 uvreq->sock->statsindex[STATID_SENDFAIL]);
	}

	uvreq->cb.send(uvreq->handle, result, uvreq->cbarg);
	isc_nmhandle_unref(uvreq->handle);
	isc__nm_uvreq_put(&uvreq, uvreq->sock);
}

/*
 * udp_send_direct sends buf to a peer on a socket. Sock has to be in
 * the same thread as the callee.
 */
static isc_result_t
udp_send_direct(isc_nmsocket_t *sock, isc__nm_uvreq_t *req,
		isc_sockaddr_t *peer) {
	int rv;

	REQUIRE(sock->tid == isc_nm_tid());
	REQUIRE(sock->type == isc_nm_udpsocket);

	if (!isc__nmsocket_active(sock)) {
		return (ISC_R_CANCELED);
	}
	isc_nmhandle_ref(req->handle);
	const struct sockaddr *sa = sock->connected ? NULL : &peer->type.sa;
	rv = uv_udp_send(&req->uv_req.udp_send, &sock->uv_handle.udp,
			 &req->uvbuf, 1, sa, udp_send_cb);
	if (rv < 0) {
		isc__nm_incstats(req->sock->mgr,
				 req->sock->statsindex[STATID_SENDFAIL]);
		return (isc__nm_uverr2result(rv));
	}

	return (ISC_R_SUCCESS);
}

/*
 * handle 'udpconnect' async call - open a UDP socket and call the open
 * callback with a handle.
 */
void
isc__nm_async_udpconnect(isc__networker_t *worker, isc__netievent_t *ev0) {
	isc__netievent_udpconnect_t *ievent =
		(isc__netievent_udpconnect_t *)ev0;
	isc_nmsocket_t *sock = ievent->sock;
	isc_nmhandle_t *handle = NULL;
	int uv_bind_flags = UV_UDP_REUSEADDR;
	int r;

	REQUIRE(sock->type == isc_nm_udpsocket);
	REQUIRE(sock->iface != NULL);
	REQUIRE(sock->parent == NULL);
	REQUIRE(sock->tid == isc_nm_tid());

	uv_udp_init(&worker->loop, &sock->uv_handle.udp);
	uv_handle_set_data(&sock->uv_handle.handle, NULL);
	uv_handle_set_data(&sock->uv_handle.handle, sock);
	handle = isc__nmhandle_get(sock, &ievent->peer, &sock->iface->addr);

	r = uv_udp_open(&sock->uv_handle.udp, sock->fd);
	if (r != 0) {
		isc__nm_incstats(sock->mgr, sock->statsindex[STATID_OPENFAIL]);
		atomic_store(&sock->closed, true);
		atomic_store(&sock->connect_error, true);
		sock->result = isc__nm_uverr2result(r);
		goto done;
	}
	isc__nm_incstats(sock->mgr, sock->statsindex[STATID_OPEN]);

	if (sock->iface->addr.type.sa.sa_family == AF_INET6) {
		uv_bind_flags |= UV_UDP_IPV6ONLY;
	}

	r = uv_udp_bind(&sock->uv_handle.udp,
			&sock->iface->addr.type.sa, uv_bind_flags);
	if (r != 0) {
		isc__nm_incstats(sock->mgr, sock->statsindex[STATID_BINDFAIL]);
		atomic_store(&sock->connect_error, true);
		sock->result = isc__nm_uverr2result(r);
		goto done;
	}

	r = uv_udp_connect(&sock->uv_handle.udp, &ievent->peer.type.sa);
	if (r != 0) {
		isc__nm_incstats(sock->mgr,
				 sock->statsindex[STATID_CONNECTFAIL]);
		atomic_store(&sock->connect_error, true);
		sock->result = isc__nm_uverr2result(r);
		goto done;
	}
	isc__nm_incstats(sock->mgr, sock->statsindex[STATID_CONNECT]);

#ifdef ISC_RECV_BUFFER_SIZE
	uv_recv_buffer_size(&sock->uv_handle.handle,
			    &(int){ ISC_RECV_BUFFER_SIZE });
#endif
#ifdef ISC_SEND_BUFFER_SIZE
	uv_send_buffer_size(&sock->uv_handle.handle,
			    &(int){ ISC_SEND_BUFFER_SIZE });
#endif

	atomic_store(&sock->connected, true);
	sock->result = ISC_R_SUCCESS;

done:
	sock->rcb.connect(handle, sock->result, sock->rcbarg);

	LOCK(&sock->lock);
	SIGNAL(&sock->cond);
	UNLOCK(&sock->lock);

	isc__nmsocket_detach(&sock);
}

isc_result_t
isc_nm_udpconnect(isc_nm_t *mgr, isc_nmiface_t *local, isc_nmiface_t *peer,
		  isc_nm_cb_t cb, void *cbarg, size_t extrahandlesize) {
	isc_result_t result = ISC_R_SUCCESS;
	isc_nmsocket_t *sock = NULL, *tmp = NULL;
	isc__netievent_udpconnect_t *event = NULL;
	int r = 0;

	REQUIRE(VALID_NM(mgr));
	REQUIRE(local != NULL);
	REQUIRE(peer != NULL);

	sock = isc_mem_get(mgr->mctx, sizeof(isc_nmsocket_t));
	isc__nmsocket_init(sock, mgr, isc_nm_udpsocket, local);

	INSIST(sock->rcb.recv == NULL && sock->rcbarg == NULL);
	sock->rcb.connect = cb;
	sock->rcbarg = cbarg;
	sock->extrahandlesize = extrahandlesize;
	sock->peer = peer->addr;
	sock->client = true;

	sock->fd = socket(peer->addr.type.sa.sa_family, SOCK_DGRAM, 0);
	RUNTIME_CHECK(sock->fd >= 0);

	/*
	 * Set up SO_REUSE* (see comments in isc_nm_listenudp() for
	 * details).
	 */
#if defined(SO_REUSEADDR)
	r = setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 },
		       sizeof(int));
	RUNTIME_CHECK(r == 0);
#endif
#if defined(SO_REUSEPORT_LB)
	r = setsockopt(sock->fd, SOL_SOCKET, SO_REUSEPORT_LB, &(int){ 1 },
		       sizeof(int));
	RUNTIME_CHECK(r == 0);
#elif defined(SO_REUSEPORT)
	r = setsockopt(sock->fd, SOL_SOCKET, SO_REUSEPORT, &(int){ 1 },
		       sizeof(int));
	RUNTIME_CHECK(r == 0);
#endif

#ifdef SO_INCOMING_CPU
	(void)setsockopt(sock->fd, SOL_SOCKET, SO_INCOMING_CPU, &(int){ 1 },
			 sizeof(int));
#endif

	event = isc__nm_get_ievent(mgr, netievent_udpconnect);
	event->sock = sock;
	event->peer = *((isc_sockaddr_t*)peer);

	/*
	 * Hold an additional sock reference so async callbacks
	 * can't destroy it until we're ready.
	 */
	isc__nmsocket_attach(sock, &tmp);

	r = isc_random_uniform(mgr->nworkers);
	if (r == isc_nm_tid()) {
		isc__nm_async_udpconnect(&mgr->workers[r],
				      (isc__netievent_t *)event);
		isc__nm_put_ievent(mgr, event);
	} else {
		isc__nm_enqueue_ievent(&mgr->workers[r],
				       (isc__netievent_t *)event);

		LOCK(&sock->lock);
		while (!atomic_load(&sock->connected) &&
		       !atomic_load(&sock->connect_error)) {
			WAIT(&sock->cond, &sock->lock);
		}
		UNLOCK(&sock->lock);
	}

	if (sock->result != ISC_R_SUCCESS) {
		result = sock->result;
		isc__nmsocket_detach(&sock);
	}

	isc__nmsocket_detach(&tmp);

	return (result);
}

static void
udp_read_cb(uv_udp_t *handle, ssize_t nrecv, const uv_buf_t *buf,
	    const struct sockaddr *addr, unsigned flags) {
	isc_nmsocket_t *sock = uv_handle_get_data((uv_handle_t *)handle);

	udp_recv_cb(handle, nrecv, buf, addr, flags);
	uv_udp_recv_stop(&sock->uv_handle.udp);
}

/*
 * handle 'udpread' async call - start or resume reading on a socket;
 * stop and call recv callback after each datagram.
 */
void
isc__nm_async_udpread(isc__networker_t *worker, isc__netievent_t *ev0) {
	isc__netievent_udpread_t *ievent = (isc__netievent_udpread_t *)ev0;
	isc_nmsocket_t *sock = ievent->sock;

	UNUSED(worker);

	uv_udp_recv_start(&sock->uv_handle.udp, isc__nm_alloc_cb, udp_read_cb);
}

isc_result_t
isc__nm_udp_read(isc_nmhandle_t *handle, isc_nm_recv_cb_t cb, void *cbarg) {
	isc_nmsocket_t *sock = NULL;
	isc__netievent_startread_t *ievent = NULL;

	REQUIRE(VALID_NMHANDLE(handle));
	REQUIRE(VALID_NMSOCK(handle->sock));
	REQUIRE(handle->sock->type == isc_nm_udpsocket);

	sock = handle->sock;
	sock->rcb.recv = cb;
	sock->rcbarg = cbarg;

	ievent = isc__nm_get_ievent(sock->mgr, netievent_udpread);
	ievent->sock = sock;

	if (sock->tid == isc_nm_tid()) {
		isc__nm_async_udpread(&sock->mgr->workers[sock->tid],
				      (isc__netievent_t *)ievent);
		isc__nm_put_ievent(sock->mgr, ievent);
	} else {
		isc__nm_enqueue_ievent(&sock->mgr->workers[sock->tid],
				       (isc__netievent_t *)ievent);
	}

	return (ISC_R_SUCCESS);
}

static void
udp_close_cb(uv_handle_t *uvhandle) {
	isc_nmsocket_t *sock = uv_handle_get_data(uvhandle);

	REQUIRE(VALID_NMSOCK(sock));

	isc__nm_incstats(sock->mgr, sock->statsindex[STATID_CLOSE]);
	atomic_store(&sock->closed, true);
	isc__nmsocket_prep_destroy(sock);
}

void
isc__nm_async_udpclose(isc__networker_t *worker, isc__netievent_t *ev0) {
	isc__netievent_udpclose_t *ievent = (isc__netievent_udpclose_t *)ev0;
	isc_nmsocket_t *sock = ievent->sock;

	REQUIRE(worker->id == ievent->sock->tid);

	uv_close(&sock->uv_handle.handle, udp_close_cb);
}

void
isc__nm_udp_close(isc_nmsocket_t *sock) {
	isc__netievent_udpclose_t *ievent = NULL;

	REQUIRE(VALID_NMSOCK(sock));
	REQUIRE(sock->type == isc_nm_udpsocket);

	ievent = isc__nm_get_ievent(sock->mgr, netievent_udpclose);
	ievent->sock = sock;

	if (sock->tid == isc_nm_tid()) {
		isc__nm_async_udpclose(&sock->mgr->workers[sock->tid],
				       (isc__netievent_t *)ievent);
		isc__nm_put_ievent(sock->mgr, ievent);
	} else {
		isc__nm_enqueue_ievent(&sock->mgr->workers[sock->tid],
				       (isc__netievent_t *)ievent);
	}
}
