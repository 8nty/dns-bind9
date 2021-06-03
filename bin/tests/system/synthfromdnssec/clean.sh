#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ./*/named.memstats
rm -f ./*/named.conf
rm -f ./*/named.run
rm -f ./dig.out.*
rm -f ./ns1/K*+*+*.key
rm -f ./ns1/K*+*+*.private
rm -f ./ns1/dsset-*
rm -f ./ns1/example.db
rm -f ./ns1/example.db.signed
rm -f ./ns1/dnamed.db
rm -f ./ns1/dnamed.db.signed
rm -f ./ns1/root.db
rm -f ./ns1/root.db.signed
rm -f ./ns1/trusted.conf
rm -f ./ns2/named_dump.db
rm -f ./ns*/managed-keys.bind*
