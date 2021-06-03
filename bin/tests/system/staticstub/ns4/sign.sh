#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=sub.example
infile=${zone}.db.in
zonefile=${zone}.db

keyname1=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone $zone`
keyname2=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -f KSK -n zone $zone`

cat $infile $keyname1.key $keyname2.key > $zonefile

$SIGNER -o $zone $zonefile > /dev/null
