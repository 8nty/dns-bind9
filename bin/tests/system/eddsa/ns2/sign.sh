#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

. ../../conf.sh

zone=example.com.
infile=example.com.db.in
zonefile=example.com.db
starttime=20150729220000
endtime=20150819220000

echo_i "ns2/sign.sh"

cp $infile $zonefile

if [ -f ../ed25519-supported.file ]; then

	for i in Xexample.com.+015+03613 Xexample.com.+015+35217
	do
		cp "$i.key" "$(echo $i.key | sed s/X/K/)"
		cp "$i.private" "$(echo $i.private | sed s/X/K/)"
		cat "$(echo $i.key | sed s/X/K/)" >> "$zonefile"
	done
fi

$SIGNER -P -z -s "$starttime" -e "$endtime" -o "$zone" "$zonefile" > /dev/null 2> signer.err || cat signer.err
