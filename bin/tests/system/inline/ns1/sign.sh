#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
rm -f K.+*+*.key
rm -f K.+*+*.private
keyname=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone $zone`
keyname=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone -f KSK $zone`
$SIGNER -S -x -T 1200 -o ${zone} root.db > signer.out
[ $? = 0 ] || cat signer.out

keyfile_to_static_ds $keyname > trusted.conf
cp trusted.conf ../ns6/trusted.conf
