#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

status=0

(
$SHELL -c "while true
           do $RNDC -c ../common/rndc.conf -s 10.53.0.3 -p 9953 reload 2>&1 |
	       sed 's/^/I:ns3 /';
	   sleep 1
       done" & echo $! >reload.pid
) &

for i in 0 1 2 3 4
do
       $PERL update.pl -s 10.53.0.2 -p 5300 zone00000$i.example. &
done

echo_i "waiting for background processes to finish"
wait

echo_i "killing reload loop"
kill `cat reload.pid`

echo_i "exit status: $status"
[ $status -eq 0 ] || exit 1
