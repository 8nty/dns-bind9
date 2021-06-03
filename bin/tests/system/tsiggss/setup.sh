#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$SHELL clean.sh

copy_setports ns1/named.conf.in ns1/named.conf

key=`$KEYGEN -Cq -K ns1 -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS -n HOST -T KEY key.example.nil.`
cat ns1/example.nil.db.in ns1/${key}.key > ns1/example.nil.db
