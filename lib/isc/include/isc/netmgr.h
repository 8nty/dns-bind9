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

#pragma once

#include <config.h>

#include <isc/mem.h>
#include <isc/result.h>
#include <isc/types.h>

typedef enum {
	NMEV_READ,
	NMEV_WRITE,
	NMEV_ACCEPT,
	NMEV_CONNECTED,
	NMEV_CANCELLED,
	NMEV_SHUTDOWN
} isc_nm_eventtype;

isc_nm_t *
isc_nm_start(isc_mem_t *mctx, uint32_t workers);
/*%<
 * Creates a new network manager with 'workers' worker threads,
 * and starts it running.
 */

void
isc_nm_shutdown(isc_nm_t **mgr);
/*
 * Signals that the network manager should begin an orderly shutdown.
 * All pending callbacks are executed with status UV_CANCELED so that
 * handles can be freed. Once all references to the manager are detached,
 * its resources are freed and '*mgr' is set to NULL.
 */

void
isc_nm_attach(isc_nm_t *mgr, isc_nm_t **dst);
void
isc_nm_detach(isc_nm_t **mgr0);
/*%<
 * Attach/detach a network manager. When all references have been
 * released, the network manager is shut down, freeing all resources.
 * (This cannot ordinarily occur until after a shutdown has been started.)
 */

/* Return thread id of current thread, or ISC_NETMGR_TID_UNKNOWN */
int
isc_nm_tid(void);

/*
 * isc_nm_freehandle frees a handle, releasing resources
 */
void
isc_nm_freehandle(isc_nmhandle_t *handle);

void
isc_nmsocket_attach(isc_nmsocket_t *sock, isc_nmsocket_t **target);
/*%<
 * isc_nmsocket_attach attaches to a socket, increasing refcount
 */

void
isc_nmsocket_close(isc_nmsocket_t *sock);

void
isc_nmsocket_detach(isc_nmsocket_t **socketp);
/*%<
 * isc_nmsocket_detach detaches from socket, decreasing refcount
 * and possibly destroying the socket if it's no longer referenced.
 */

void
isc_nmhandle_attach(isc_nmhandle_t *handle, isc_nmhandle_t **handlep);

void
isc_nmhandle_detach(isc_nmhandle_t **handlep);

void *
isc_nmhandle_getdata(isc_nmhandle_t *handle);

void *
isc_nmhandle_getextra(isc_nmhandle_t *handle);

typedef void (*isc_nm_opaquecb)(void *arg);

bool
isc_nmhandle_is_stream(isc_nmhandle_t *handle);

/*
 * isc_nmhandle_t has a void * opaque field (usually - ns_client_t).
 * We reuse handle and `opaque` can also be reused between calls.
 * This function sets this field and two callbacks:
 * - doreset resets the `opaque` to initial state
 * - dofree frees everything associated with `opaque`
 */
void
isc_nmhandle_setdata(isc_nmhandle_t *handle, void *arg,
		     isc_nm_opaquecb doreset, isc_nm_opaquecb dofree);

isc_sockaddr_t
isc_nmhandle_peeraddr(isc_nmhandle_t *handle);

typedef void (*isc_nm_recv_cb_t)(isc_nmhandle_t *handle, isc_region_t *region,
				 void *cbarg);
/*%<
 * Callback function to be used when receiving a packet.
 *
 * 'handle' the handle that can be used to send back the answer.
 * 'region' contains the received data. It will be freed after
 *          return by caller.
 * 'cbarg'  the callback argument passed to isc_nm_listenudp(),
 *          isc_nm_listentcpdns(), or isc_nm_read().
 */

typedef void (*isc_nm_cb_t)(isc_nmhandle_t *handle, isc_result_t result,
			    void *cbarg);
/*%<
 * Callback function for other network completion events (send, connect,
 * accept).
 *
 * 'handle' the handle on which the event took place.
 * 'result' the result of the event.
 * 'cbarg'  the callback argument passed to isc_nm_send(),
 *          isc_nm_tcp_connect(), or isc_nm_listentcp()
 */

isc_result_t
isc_nm_listenudp(isc_nm_t *mgr, isc_nmiface_t *iface,
		 isc_nm_recv_cb_t cb, void *cbarg,
		 size_t extrasize, isc_nmsocket_t **sockp);
/*%<
 * Start listening for UDP packets on interface 'iface' using net manager
 * 'mgr'.
 *
 * On success, 'sockp' will be updated to contain a new listening UDP socket.
 *
 * When a packet is received on the socket, 'cb' will be called with 'cbarg'
 * as its argument.
 *
 * When handles are allocated for the socket, 'extrasize' additional bytes
 * will be allocated along with the handle for an associated object
 * (typically ns_client).
 */

void
isc_nm_udp_stoplistening(isc_nmsocket_t *sock);
/*%<
 * Stop listening for UDP packets on socket 'sock'.
 */

void
isc_nm_pause(isc_nm_t *mgr);
/*%<
 * Pause all processing, equivalent to taskmgr exclusive tasks.
 * It won't return until all workers have been paused.
 */

void
isc_nm_resume(isc_nm_t *mgr);
/*%<
 * Resume paused processing. It will return immediately
 * after signalling workers to resume.
 */

isc_result_t
isc_nm_read(isc_nmhandle_t *handle, isc_nm_recv_cb_t cb, void *cbarg);

isc_result_t
isc_nm_pauseread(isc_nmsocket_t *sock);
/*%<
 * Pause reading on this socket, while still remembering the callback.
 */

isc_result_t
isc_nm_resumeread(isc_nmsocket_t *sock);
/*%<
 * Resume reading from socket.
 *
 * Requires:
 * \li	'sock' is a valid netmgr socket
 * \li	...for which a read/recv callback has been defined.
 */

isc_result_t
isc_nm_send(isc_nmhandle_t *handle, isc_region_t *region,
	    isc_nm_cb_t cb, void *cbarg);
/*%<
 * Send the data in 'region' via 'handle'. Afterward, the callback 'cb' is
 * called with the argument 'cbarg'.
 *
 * 'region' is not copied; it has to be allocated beforehand and freed
 * in 'cb'.
 */

isc_result_t
isc_nm_listentcp(isc_nm_t *mgr, isc_nmiface_t *iface,
		 isc_nm_cb_t cb, void *cbarg,
		 size_t extrahandlesize, isc_quota_t *quota,
		 isc_nmsocket_t **rv);
/*%<
 * Start listening for raw messages over the TCP interface 'iface', using
 * net manager 'mgr'.
 *
 * On success, 'sockp' will be updated to contain a new listening TCP
 * socket.
 *
 * When a message is received on the socket, 'cb' will be called with 'cbarg'
 * as its argument.
 *
 * When handles are allocated for the socket, 'extrasize' additional bytes
 * will be allocated along with the handle for an associated object.
 *
 * If 'quota' is not NULL, then the socket is attached to the specified
 * quota. This allows us to enforce TCP client quota limits.
 *
 * NOTE: This is currently only called inside isc_nm_listentcpdns(), which
 * creates a 'wrapper' socket that sends and receives DNS messages -
 * prepended with a two-byte length field - and handles buffering.
 */

void
isc_nm_tcp_stoplistening(isc_nmsocket_t *sock);
/*%<
 * Stop listening on TCP socket 'sock'.
 */

isc_result_t
isc_nm_listentcpdns(isc_nm_t *mgr, isc_nmiface_t *iface,
		     isc_nm_recv_cb_t cb, void *arg,
		     size_t extrahandlesize, isc_quota_t *quota,
		     isc_nmsocket_t **sockp);
/*%<
 * Start listening for DNS messages over the TCP interface 'iface', using
 * net manager 'mgr'.
 *
 * On success, 'sockp' will be updated to contain a new listening TCPDNS
 * socket. This is a wrapper around a TCP socket, and handles DNS length
 * processing.
 *
 * When a complete DNS message is received on the socket, 'cb' will be
 * called with 'cbarg' as its argument.
 *
 * When handles are allocated for the socket, 'extrasize' additional bytes
 * will be allocated along with the handle for an associated object
 * (typically ns_client).
 */

void
isc_nm_tcpdns_stoplistening(isc_nmsocket_t *sock);
/*%<
 * Stop listening on TCPDNS socket 'sock'.
 */

void
isc_nm_tcpdns_sequential(isc_nmhandle_t *handle);
/*%<
 * Disable pipelining on this connection. Each DNS packet
 * will be only processed after the previous completes.
 *
 * This cannot be reversed once set for a given connection
 */
