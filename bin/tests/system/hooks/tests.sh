#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

status=0
n=0

rm -f dig.out.*

DIGOPTS="+tcp +noadd +nosea +nostat +nocmd -p ${PORT}"
RNDCCMD="$RNDC -c ../common/rndc.conf -p ${CONTROLPORT} -s"

n=$((n+1))
echo_i "checking asynchronous hook action resumes correctly ($n)"
ret=0
$DIG $DIGOPTS example.com @10.53.0.1 > dig.out.ns1.test$n || ret=1
# the test-async plugin changes the status of any postiive answer to NOTIMP
grep -q "status: NOTIMP" dig.out.ns1.test$n || ret=1
if [ $ret != 0 ]; then echo_i "failed"; fi
status=$((status + ret))



echo_i "exit status: $status"
[ $status -eq 0 ] || exit 1
