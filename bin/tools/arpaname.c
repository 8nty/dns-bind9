/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <stdio.h>

#include <isc/net.h>
#include <isc/print.h>

#define UNUSED(x) (void)(x)

int
main(int argc, char *argv[]) {
	unsigned char buf[16];
	int i;

	UNUSED(argc);

	while (argv[1]) {
		if (inet_pton(AF_INET6, argv[1], buf) == 1) {
			for (i = 15; i >= 0; i--) {
				fprintf(stdout, "%X.%X.", buf[i] & 0xf,
					(buf[i] >> 4) & 0xf);
			}
			fprintf(stdout, "IP6.ARPA\n");
			argv++;
			continue;
		}
		if (inet_pton(AF_INET, argv[1], buf) == 1) {
			fprintf(stdout, "%u.%u.%u.%u.IN-ADDR.ARPA\n", buf[3],
				buf[2], buf[1], buf[0]);
			argv++;
			continue;
		}
		return (1);
	}
	fflush(stdout);
	return (ferror(stdout));
}
