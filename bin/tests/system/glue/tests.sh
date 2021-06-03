#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

#
# Do glue tests.
#

DIGOPTS="+norec -p ${PORT}"

status=0

echo_i "testing that a ccTLD referral gets a full glue set from the root zone"
$DIG $DIGOPTS @10.53.0.1 foo.bar.fi. A >dig.out || status=1
digcomp --lc fi.good dig.out || status=1

echo_i "testing that we don't find out-of-zone glue"
$DIG $DIGOPTS @10.53.0.1 example.net. a > dig.out || status=1
digcomp noglue.good dig.out || status=1

echo_i "exit status: $status"
[ $status -eq 0 ] || exit 1
