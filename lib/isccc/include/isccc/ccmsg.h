/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef ISCCC_CCMSG_H
#define ISCCC_CCMSG_H 1

/*! \file isccc/ccmsg.h */

#include <inttypes.h>

#include <isc/buffer.h>
#include <isc/lang.h>
#include <isc/netmgr.h>
#include <isc/sockaddr.h>

/*% ISCCC Message Structure */
typedef struct isccc_ccmsg {
	/* private (don't touch!) */
	unsigned int	magic;
	uint32_t	size;
	bool		length_received;
	isc_buffer_t *	buffer;
	unsigned int	maxsize;
	isc_mem_t *	mctx;
	isc_nmhandle_t *handle;
	isc_nm_cb_t	cb;
	void *		cbarg;
	bool		reading;
	/* public (read-only) */
	isc_result_t result;
} isccc_ccmsg_t;

ISC_LANG_BEGINDECLS

void
isccc_ccmsg_init(isc_mem_t *mctx, isc_nmhandle_t *handle, isccc_ccmsg_t *ccmsg);
/*%
 * Associate a cc message state with a given memory context and
 * netmgr handle. (Note that the caller must hold a reference to
 * the handle during asynchronous ccmsg operations; the ccmsg code
 * does not hold the reference itself.)
 *
 * Requires:
 *
 *\li	"mctx" be a valid memory context.
 *
 *\li	"handle" be a netmgr handle for a stream socket.
 *
 *\li	"ccmsg" be non-NULL and an uninitialized or invalidated structure.
 *
 * Ensures:
 *
 *\li	"ccmsg" is a valid structure.
 */

void
isccc_ccmsg_setmaxsize(isccc_ccmsg_t *ccmsg, unsigned int maxsize);
/*%
 * Set the maximum packet size to "maxsize"
 *
 * Requires:
 *
 *\li	"ccmsg" be valid.
 *
 *\li	512 <= "maxsize" <= 4294967296
 */

void
isccc_ccmsg_readmessage(isccc_ccmsg_t *ccmsg, isc_nm_cb_t cb, void *cbarg);
/*%
 * Schedule an event to be delivered when a command channel message is
 * readable, or when an error occurs on the socket.
 *
 * Requires:
 *
 *\li	"ccmsg" be valid.
 *
 * Notes:
 *
 *\li	The event delivered is a fully generic event.  It will contain no
 *	actual data.  The sender will be a pointer to the isccc_ccmsg_t.
 *	The result code inside that structure should be checked to see
 *	what the final result was.
 */

void
isccc_ccmsg_cancelread(isccc_ccmsg_t *ccmsg);
/*%
 * Cancel a readmessage() call.  The event will still be posted with a
 * CANCELED result code.
 *
 * Requires:
 *
 *\li	"ccmsg" be valid.
 */

void
isccc_ccmsg_invalidate(isccc_ccmsg_t *ccmsg);
/*%
 * Clean up all allocated state, and invalidate the structure.
 *
 * Requires:
 *
 *\li	"ccmsg" be valid.
 *
 * Ensures:
 *
 *\li	"ccmsg" is invalidated and disassociated with all memory contexts,
 *	sockets, etc.
 */

ISC_LANG_ENDDECLS

#endif /* ISCCC_CCMSG_H */
