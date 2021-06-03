#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

# We sign the zone here and move the signed zone to ns6.
# The ns5 server actually does not serve this zone but
# the DS and NS records are in the test root zone, and
# delegate to ns6.
zone=signed.
infile=signed.db.in
zonefile=signed.db

key1=`$KEYGEN -q -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS $zone 2> /dev/null`
key2=`$KEYGEN -q -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS -fk $zone 2> /dev/null`

cat $infile $key1.key $key2.key > $zonefile

$SIGNER -P -g -O full -o $zone $zonefile > sign.ns5.signed.out

cp signed.db.signed ../ns6

# Root zone.
zone=.
infile=root.db.in
zonefile=root.db

key1=`$KEYGEN -q -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS $zone 2> /dev/null`
key2=`$KEYGEN -q -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS -fk $zone 2> /dev/null`

# cat $infile $key1.key $key2.key > $zonefile
cat $infile dsset-signed. $key1.key $key2.key > $zonefile

$SIGNER -P -g -O full -o $zone $zonefile > sign.ns5.root.out
