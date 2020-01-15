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
#include <isc/log.h>
#include "uv-compat.h"

/*
 * XXXWPK: This code goes into libuv internals and it's platform dependent.
 * It's ugly, we shouldn't do it, but the alternative with passing sockets
 * over IPC sockets is even worse, and causes all kind of different
 * problems. We should try to push these things upstream.
 */

#ifdef WIN32
/* This code is adapted from libuv/src/win/internal.h */
typedef enum {
	UV__IPC_SOCKET_XFER_NONE = 0,
	UV__IPC_SOCKET_XFER_TCP_CONNECTION,
	UV__IPC_SOCKET_XFER_TCP_SERVER
} uv__ipc_socket_xfer_type_t;

typedef struct {
	WSAPROTOCOL_INFOW socket_info;
	uint32_t delayed_error;
} uv__ipc_socket_xfer_info_t;

int
uv__tcp_xfer_import(uv_tcp_t *tcp, uv__ipc_socket_xfer_type_t xfer_type,
		    uv__ipc_socket_xfer_info_t *xfer_info);

int
uv__tcp_xfer_export(uv_tcp_t* handle,
                    int target_pid,
                    uv__ipc_socket_xfer_type_t* xfer_type,
                    uv__ipc_socket_xfer_info_t* xfer_info);

int
isc_uv_export(uv_stream_t *stream, isc_uv_stream_info_t *info) {
	uv__ipc_socket_xfer_info_t xfer_info;
	uv__ipc_socket_xfer_type_t xfer_type;
	isc_log_write(isc_lctx, ISC_LOGCATEGORY_GENERAL,
		      ISC_LOGMODULE_NETMGR, ISC_LOG_ERROR,
		      "uv_export sizeofs 1 %d 2 %d", sizeof(isc_uv_stream_info_t), sizeof(uv__ipc_socket_xfer_info_t));
	if (stream->type != UV_TCP) {
		isc_log_write(isc_lctx, ISC_LOGCATEGORY_GENERAL,
			      ISC_LOGMODULE_NETMGR, ISC_LOG_ERROR,
			      "uv_export failed: stream not tcp");
		return (-1);
	}
	int r = uv__tcp_xfer_export((uv_tcp_t *) stream, GetCurrentProcessId(), &xfer_type, &xfer_info);
	if (r != 0) {
		isc_log_write(isc_lctx, ISC_LOGCATEGORY_GENERAL,
			      ISC_LOGMODULE_NETMGR, ISC_LOG_ERROR,
			      "uv_export failed: result %d", r);
		return (r);
	}
	if (xfer_info.delayed_error != 0) {
		isc_log_write(isc_lctx, ISC_LOGCATEGORY_GENERAL,
			      ISC_LOGMODULE_NETMGR, ISC_LOG_ERROR,
			      "uv_export failed: delayed error %d", xfer_info.delayed_error);
		return (xfer_info.delayed_error);
	}
	info->type = UV_TCP;
	info->socket_info = xfer_info.socket_info;
	return (0);
}

int
isc_uv_import(uv_stream_t *stream, isc_uv_stream_info_t *info) {
	uv__ipc_socket_xfer_info_t xfer_info;

	if (stream->type != UV_TCP || info->type != UV_TCP) {
		return (-1);
	}
	xfer_info.delayed_error = 0;
	xfer_info.socket_info = info->socket_info;

	return (uv__tcp_xfer_import((uv_tcp_t *) stream,
				    UV__IPC_SOCKET_XFER_TCP_SERVER,
				    &xfer_info));
}
#else /* WIN32 */
/* Adapted from libuv/src/unix/internal.h */
#include <sys/ioctl.h>
#include <fcntl.h>

static int
isc_uv__cloexec(int fd, int set) {
	int r;

	/*
	 * This #ifdef is taken directly from the libuv sources.
	 * We use FIOCLEX and FIONCLEX ioctl() calls when possible,
	 * but on some platforms are not implemented, or defined but
	 * not implemented correctly. On those, we use the FD_CLOEXEC
	 * fcntl() call, which adds extra system call overhead, but
	 * works.
	 */
#if defined(_AIX) || \
    defined(__APPLE__) || \
    defined(__DragonFly__) || \
    defined(__FreeBSD__) || \
    defined(__FreeBSD_kernel__) || \
    defined(__linux__) || \
    defined(__OpenBSD__) || \
    defined(__NetBSD__)
	do {
		r = ioctl(fd, set ? FIOCLEX : FIONCLEX);
	} while (r == -1 && errno == EINTR);
#else /* FIOCLEX/FIONCLEX unsupported */
	int flags;

	do {
		r = fcntl(fd, F_GETFD);
	} while (r == -1 && errno == EINTR);

	if (r == -1) {
		return (-1);
	}

	if (!!(r & FD_CLOEXEC) == !!set) {
		return (0);
	}

	if (set) {
		flags = r | FD_CLOEXEC;
	} else {
		flags = r & ~FD_CLOEXEC;
	}

	do {
		r = fcntl(fd, F_SETFD, flags);
	} while (r == -1 && errno == EINTR);
#endif /* FIOCLEX/FIONCLEX unsupported */

	if (r != 0) {
		return (-1);
	}

	return (0);
}

int
isc_uv_export(uv_stream_t *stream, isc_uv_stream_info_t *info) {
	int oldfd, fd;
	int err;

	if (stream->type != UV_TCP) {
		return (-1);
	}
	err = uv_fileno((uv_handle_t *) stream, (uv_os_fd_t *) &oldfd);

	if (err != 0) {
		return (err);
	}

	fd = dup(oldfd);
	if (fd == -1) {
		return (-1);
	}

	err = isc_uv__cloexec(fd, 1);
	if (err != 0) {
		close(fd);
		return (err);
	}

	info->type = stream->type;
	info->fd = fd;
	return (0);
}

int
isc_uv_import(uv_stream_t *stream, isc_uv_stream_info_t *info) {
	if (info->type != UV_TCP) {
		return (-1);
	}

	uv_tcp_t *tcp = (uv_tcp_t *) stream;
	return (uv_tcp_open(tcp, info->fd));
}
#endif
