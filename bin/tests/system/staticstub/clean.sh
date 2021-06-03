#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f tmp
rm -f dig.out.*
rm -f ns*/named.lock
rm -f ns*/named.conf
rm -f ns3/example.db
rm -f ns3/undelegated.db
rm -f ns4/sub.example.db
rm -f ns?/named.memstats
rm -f ns?/named.run
rm -f ns?/named_dump.db
rm -rf */*.signed
rm -rf */K*
rm -rf */dsset-*
rm -rf */trusted.conf
rm -f ns*/managed-keys.bind*
