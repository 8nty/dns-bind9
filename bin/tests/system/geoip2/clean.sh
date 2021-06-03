#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ns2/named.conf
rm -f ns2/example*.db
rm -f dig.out.* rndc.out.*
rm -f ns?/named.run
rm -f ns?/named.memstats
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
