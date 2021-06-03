#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
infile=root.db.in
zonefile=root.db

keyname=`$KEYGEN -q -a RSASHA256 -b 1024 -n zone $zone`
keyid=`expr ${keyname} : 'K.+008+\(.*\)'`

(cd ../ns2 && $SHELL sign.sh ${keyid:-00000} )

cp ../ns2/dsset-example$TP .

cat $infile $keyname.key > $zonefile

$SIGNER -P -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a static key.
keyfile_to_static_ds $keyname > trusted.conf
cp trusted.conf ../ns2/trusted.conf
cp trusted.conf ../ns3/trusted.conf
cp trusted.conf ../ns4/trusted.conf
