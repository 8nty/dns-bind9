#!/bin/sh 

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
infile=root.db.in
zonefile=root.db

(cd ../ns2 && $SHELL -e sign.sh )

cp ../ns2/dsset-example$TP .
cp ../ns2/dsset-example.com$TP .

keyname1=`$KEYGEN -q -a RSASHA256 -b 1024 -n zone $zone`
keyname2=`$KEYGEN -q -a RSASHA256 -b 2048 -f KSK -n zone $zone`
cat $infile $keyname1.key $keyname2.key > $zonefile

$SIGNER -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a static key.
keyfile_to_static_ds $keyname2 > trusted.conf
cp trusted.conf ../ns2/trusted.conf
cp trusted.conf ../ns3/trusted.conf
cp trusted.conf ../ns4/trusted.conf
