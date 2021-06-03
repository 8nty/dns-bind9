#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# Run system tests that must be run sequentially
#
# Note: Use "make check" (or runall.sh) to run all the system tests.  This
# script will just run those tests that require that each of their nameservers
# is the only one running on an IP address.
#

. ./conf.sh

for d in $SEQUENTIALDIRS
do
    $SHELL run.sh "${@}" "$d" 2>&1 | tee "test.output.$d"
done
