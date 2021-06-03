#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
infile=root.db.in
zonefile=root.db

(cd ../ns2 && $SHELL sign.sh)

cp ../ns2/dsset-good$TP .
cp ../ns2/dsset-bad$TP .

key1=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone $zone`
key2=`$KEYGEN -q -a RSASHA1 -b 2048 -n zone -f KSK $zone`

cat $infile $key1.key $key2.key > $zonefile

$SIGNER -P -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a static key.
keyfile_to_static_ds $key2 > trusted.conf
cp trusted.conf ../ns2/trusted.conf
cp trusted.conf ../ns3/trusted.conf
cp trusted.conf ../ns4/trusted.conf
