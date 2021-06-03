#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

for domain in example example.com; do
	zone=${domain}.
	infile=${domain}.db.in
	zonefile=${domain}.db

	keyname1=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone $zone`
	keyname2=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -f KSK -n zone $zone`

	cat $infile $keyname1.key $keyname2.key > $zonefile

	$SIGNER -3 bebe -o $zone $zonefile > /dev/null
done

# remove "removed" record from example.com, causing the server to
# send an apparently-invalid NXDOMAIN
sed '/^removed/d' example.com.db.signed > example.com.db.new
rm -f example.com.db.signed
mv example.com.db.new example.com.db.signed
