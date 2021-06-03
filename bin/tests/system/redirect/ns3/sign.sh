#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=signed
infile=example.db
zonefile=signed.db

key1=`$KEYGEN -q -a rsasha256 $zone`
key2=`$KEYGEN -q -a rsasha256 -fk $zone`

cat $infile $key1.key $key2.key > $zonefile

$SIGNER -P -g -o $zone $zonefile > /dev/null

zone=nsec3
infile=example.db
zonefile=nsec3.db

key1=`$KEYGEN -q -a rsasha256 -3 $zone`
key2=`$KEYGEN -q -a rsasha256 -3 -fk $zone`

cat $infile $key1.key $key2.key > $zonefile

$SIGNER -P -3 - -g -o $zone $zonefile > /dev/null
