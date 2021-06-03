#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ./*/anchor.*
rm -f ./*/named.conf
rm -f ./*/named.memstats
rm -f ./*/named.run
rm -f ./delv.out.test*
rm -f ./dig.out.*test*
rm -f ./dig.out.mm.*
rm -f ./dig.out.mn.*
rm -f ./dig.out.nm.*
rm -f ./dig.out.nn.*
rm -f ./host.out.test*
rm -f ./ns*/managed-keys.bind*
rm -f ./ns*/named.lock
rm -f ./ns2/dsset-example.
rm -f ./ns2/example.db ./ns2/K* ./ns2/keyid ./ns2/keydata
rm -f ./nslookup.out.test*
rm -f ./yamlget.out.*
