#! /bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
for QDIR in `echo "$PATH" | tr : ' '` ../../../../contrib/queryperf; do
    QPERF=$QDIR/queryperf
    if test -f $QPERF -a -x $QPERF; then
	echo $QPERF
	exit 0
    fi
done

exit 0
