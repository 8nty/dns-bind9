#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=ds.example.net
zonefile="${zone}.db"
infile="${zonefile}.in"
cp $infile $zonefile
ksk=`$KEYGEN -q -a rsasha256 -fk $zone`
zsk=`$KEYGEN -q -a rsasha256 -b 2048 $zone`
cat $ksk.key $zsk.key >> $zonefile
$SIGNER -P -o $zone $zonefile > /dev/null

zone=example.net
zonefile="${zone}.db"
infile="${zonefile}.in"
cp $infile $zonefile
ksk=`$KEYGEN -q -a rsasha256 -fk $zone`
zsk=`$KEYGEN -q -a rsasha256 $zone`
cat $ksk.key $zsk.key dsset-ds.example.net$TP >> $zonefile
$SIGNER -P -o $zone $zonefile > /dev/null

# Configure a static key to be used by delv
keyfile_to_static_ds $ksk > ../ns5/trusted.conf
