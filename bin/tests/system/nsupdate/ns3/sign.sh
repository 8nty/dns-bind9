#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=nsec3param.test.
infile=nsec3param.test.db.in
zonefile=nsec3param.test.db

keyname1=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone -f KSK $zone`
keyname2=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone $zone`

cat $infile $keyname1.key $keyname2.key >$zonefile

$SIGNER -P -3 - -H 1 -o $zone -k $keyname1 $zonefile $keyname2 > /dev/null

zone=dnskey.test.
infile=dnskey.test.db.in
zonefile=dnskey.test.db

keyname1=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone -f KSK $zone`
keyname2=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone $zone`

cat $infile $keyname1.key $keyname2.key >$zonefile

$SIGNER -P -o $zone -k $keyname1 $zonefile $keyname2 > /dev/null

zone=delegation.test.
infile=delegation.test.db.in
zonefile=delegation.test.db

keyname1=`$KEYGEN -q -a RSASHA256 -3 -f KSK $zone`
keyname2=`$KEYGEN -q -a RSASHA256 -3 $zone`

cat $infile $keyname1.key $keyname2.key >$zonefile

$SIGNER -A -3 - -P -o $zone -k $keyname1 $zonefile $keyname2 > /dev/null
