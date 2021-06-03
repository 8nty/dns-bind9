#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
infile=root.db.in
zonefile=root.db

cp ../ns2/dsset-example.in dsset-example$TP

keyname=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone $zone`

cat $infile $keyname.key > $zonefile

$SIGNER -P -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a static key.
keyfile_to_static_ds $keyname > trusted.conf
cp trusted.conf ../ns2/trusted.conf
cp trusted.conf ../ns3/trusted.conf

cd ../ns2 && $SHELL -e ./sign.sh
