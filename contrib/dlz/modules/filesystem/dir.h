/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <dirent.h>
#include <sys/types.h>

#include <dlz_minimal.h>

#define DIR_NAMEMAX 256
#define DIR_PATHMAX 1024

typedef struct direntry {
	char name[DIR_NAMEMAX];
	unsigned int length;
} direntry_t;

typedef struct dir {
	char dirname[DIR_PATHMAX];
	direntry_t entry;
	DIR *handle;
} dir_t;

void
dir_init(dir_t *dir);

isc_result_t
dir_open(dir_t *dir, const char *dirname);

isc_result_t
dir_read(dir_t *dir);

isc_result_t
dir_reset(dir_t *dir);

void
dir_close(dir_t *dir);
