/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <confgen/os.h>

int
set_user(FILE *fd, const char *user) {
	struct passwd *pw;

	pw = getpwnam(user);
	if (pw == NULL) {
		errno = EINVAL;
		return (-1);
	}
	return (fchown(fileno(fd), pw->pw_uid, -1));
}
