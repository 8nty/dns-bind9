#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

n=1
status=0

# Wait until all zones are loaded before checking SPF related logs
for i in 1 2 3 4 5 6 7 8 9 10
do
	grep "all zones loaded" ns1/named.run > /dev/null && break
	sleep 1
done

echo_i "checking that SPF warnings have been correctly generated ($n)"
ret=0

grep "zone spf/IN: loaded serial 0" ns1/named.run > /dev/null || ret=1
grep "'y.spf' found type SPF" ns1/named.run > /dev/null || ret=1
grep "'spf' found type SPF" ns1/named.run > /dev/null && ret=1

grep "zone warn/IN: loaded serial 0" ns1/named.run > /dev/null || ret=1
grep "'y.warn' found type SPF" ns1/named.run > /dev/null || ret=1
grep "'warn' found type SPF" ns1/named.run > /dev/null && ret=1

grep "zone nowarn/IN: loaded serial 0" ns1/named.run > /dev/null || ret=1
grep "'y.nowarn' found type SPF" ns1/named.run > /dev/null && ret=1
grep "'nowarn' found type SPF" ns1/named.run > /dev/null && ret=1
n=`expr $n + 1`
if [ $ret != 0 ]; then echo_i "failed"; fi
status=`expr $status + $ret`

echo_i "exit status: $status"
[ $status -eq 0 ] || exit 1
