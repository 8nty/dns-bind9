/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <isc/print.h>

#define USAGE "usage: gencheck <filename>\n"

static int
check(const char *buf, ssize_t count, size_t *start) {
	const char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	ssize_t i;

	for (i = 0; i < count; i++, *start = (*start + 1) % (sizeof(chars) - 1))
	{
		/* Just ignore the trailing newline */
		if (buf[i] == '\n') {
			continue;
		}
		if (buf[i] != chars[*start]) {
			return (0);
		}
	}

	return (1);
}

int
main(int argc, char **argv) {
	int ret;
	int fd;
	ssize_t count;
	char buf[1024];
	size_t start;
	size_t length;

	ret = EXIT_FAILURE;
	fd = -1;
	length = 0;

	if (argc != 2) {
		fprintf(stderr, USAGE);
		goto out;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		goto out;
	}

	start = 0;
	while ((count = read(fd, buf, sizeof(buf))) != 0) {
		if (count < 0) {
			goto out;
		}

		if (!check(buf, count, &start)) {
			goto out;
		}

		length += count;
	}

	ret = EXIT_SUCCESS;

out:
	printf("%lu\n", (unsigned long)length);

	if (fd != -1) {
		close(fd);
	}

	return (ret);
}
