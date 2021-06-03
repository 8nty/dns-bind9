#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in tmp
sed 's/SERVER_CONFIG_PLACEHOLDER/server-names { "ns.example.net"; };/' tmp > ns2/named.conf

copy_setports ns3/named.conf.in tmp
sed 's/EXAMPLE_ZONE_PLACEHOLDER/zone "example" { type master; file "example.db.signed"; };/' tmp > ns3/named.conf

copy_setports ns4/named.conf.in ns4/named.conf

cd ns3 && $SHELL -e sign.sh
