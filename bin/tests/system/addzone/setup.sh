#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

cp -f ns1/redirect.db.1 ns1/redirect.db
cp -f ns2/redirect.db.1 ns2/redirect.db
cp -f ns3/redirect.db.1 ns3/redirect.db

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named1.conf.in ns2/named.conf
copy_setports ns3/named1.conf.in ns3/named.conf

cp -f ns2/default.nzf.in ns2/3bf305731dd26307.nzf
mkdir ns2/new-zones
