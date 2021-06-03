#!/bin/sh 

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=example.
infile=example.db.in
zonefile=example.db

(cd ../ns4 && $SHELL -e sign.sh )

cp ../ns4/dsset-sub.example$TP .

keyname1=`$KEYGEN -q -a RSASHA256 -b 1024 -n zone $zone`
keyname2=`$KEYGEN -q -a RSASHA256 -b 2048 -f KSK -n zone $zone`
cat $infile $keyname1.key $keyname2.key > $zonefile

$SIGNER -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a trusted key.
keyfile_to_static_ds $keyname2 > trusted.conf

zone=undelegated
infile=undelegated.db.in
zonefile=undelegated.db
keyname1=`$KEYGEN -q -a RSASHA256 -b 1024 -n zone $zone`
keyname2=`$KEYGEN -q -a RSASHA256 -b 2048 -f KSK -n zone $zone`
cat $infile $keyname1.key $keyname2.key > $zonefile

$SIGNER -g -o $zone $zonefile > /dev/null

keyfile_to_static_ds $keyname2 >> trusted.conf
cp trusted.conf ../ns2/trusted.conf
