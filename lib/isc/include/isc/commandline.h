/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_COMMANDLINE_H
#define ISC_COMMANDLINE_H 1

/*! \file isc/commandline.h */

#include <stdbool.h>

#include <isc/lang.h>
#include <isc/platform.h>
#include <isc/result.h>

/*% Index into parent argv vector. */
LIBISC_EXTERNAL_DATA extern int isc_commandline_index;
/*% Character checked for validity. */
LIBISC_EXTERNAL_DATA extern int isc_commandline_option;
/*% Argument associated with option. */
LIBISC_EXTERNAL_DATA extern char *isc_commandline_argument;
/*% For printing error messages. */
LIBISC_EXTERNAL_DATA extern char *isc_commandline_progname;
/*% Print error message. */
LIBISC_EXTERNAL_DATA extern bool isc_commandline_errprint;
/*% Reset getopt. */
LIBISC_EXTERNAL_DATA extern bool isc_commandline_reset;

ISC_LANG_BEGINDECLS

int
isc_commandline_parse(int argc, char *const *argv, const char *options);
/*%<
 * Parse a command line (similar to getopt())
 */

isc_result_t
isc_commandline_strtoargv(isc_mem_t *mctx, char *s, unsigned int *argcp,
			  char ***argvp, unsigned int n);
/*%<
 * Tokenize the string "s" into whitespace-separated words,
 * returning the number of words in '*argcp' and an array
 * of pointers to the words in '*argvp'.  The caller
 * must free the array using isc_mem_free().  The string
 * is modified in-place.
 */

ISC_LANG_ENDDECLS

#endif /* ISC_COMMANDLINE_H */
