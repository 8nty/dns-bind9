#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after zone transfer quota tests.
#

rm -f ns1/zone*.example.db ns1/zones.conf
rm -f ns2/zone*.example.bk ns2/zones.conf
rm -f dig.out.* ns2/changing.bk
rm -f ns1/changing.db
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
