/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

/*
 * A little wrapper around readline(), add_history() and free() to make using
 * the readline code simpler.
 */

#if defined(HAVE_READLINE_LIBEDIT)
#include <editline/readline.h>
#elif defined(HAVE_READLINE_EDITLINE)
#include <editline.h>
#elif defined(HAVE_READLINE_READLINE)
/* Prevent deprecated functions being declared. */
#define _FUNCTION_DEF 1
/* Ensure rl_message() gets prototype. */
#define USE_VARARGS   1
#define PREFER_STDARG 1
#include <readline/history.h>
#include <readline/readline.h>
#endif

#if !defined(HAVE_READLINE_LIBEDIT) && !defined(HAVE_READLINE_EDITLINE) && \
	!defined(HAVE_READLINE_READLINE)

#include <stdio.h>
#include <stdlib.h>

#define RL_MAXCMD (128 * 1024)

static inline char *
readline(const char *prompt) {
	char *line, *buf = malloc(RL_MAXCMD);
	fprintf(stdout, "%s", prompt);
	fflush(stdout);
	line = fgets(buf, RL_MAXCMD, stdin);
	if (line == NULL) {
		free(buf);
		return (NULL);
	}
	return (buf);
};

#define add_history(line)

#endif
