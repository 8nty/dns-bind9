#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=example.
zonefile=example.db

ksk=`$KEYGEN -q -a RSASHA256 -b 2048 -fk $zone`
zsk=`$KEYGEN -q -a RSASHA256 -b 1024 $zone`
$SIGNER -S -o $zone example.db > /dev/null
