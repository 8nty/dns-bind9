#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Run a system test.
#

. ./conf.sh

test $# -gt 0 || { echo "usage: $0 test-directory" >&2; exit 1; }

test=$1
shift

test -d $test || { echo "$0: $test: no such test" >&2; exit 1; }

# Set up any dynamically generated test data
if test -f $test/setup.sh
then
   ( cd $test && $SHELL setup.sh "$@" )
fi


