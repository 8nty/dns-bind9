#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$SHELL clean.sh

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
copy_setports ns3/named.conf.in ns3/named.conf

cp -f ns1/catalog.example.db.in ns1/catalog1.example.db
cp -f ns1/catalog.example.db.in ns3/catalog2.example.db
cp -f ns1/catalog.example.db.in ns1/catalog3.example.db
cp -f ns1/catalog.example.db.in ns1/catalog4.example.db

mkdir -p ns2/zonedir
