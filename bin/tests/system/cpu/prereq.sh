#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

# shellcheck source=conf.sh
. ../conf.sh

case $(uname) in
	Linux*)
		;;
	*)
		echo_i "cpu test only runs on Linux"
		exit 255
		;;
esac

# TASKSET will be an empty string if no taskset program was found.
TASKSET=$(command -v "taskset" || true)
if ! test -x "$TASKSET" ; then
	exit 255
fi

if ! $TASKSET fff0 true > /dev/null 2>&1; then
        echo_i "taskset failed"
        exit 255
fi
