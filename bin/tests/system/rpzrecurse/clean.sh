# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

# Clean up after rpz tests.

rm -f dig.out.*

rm -f ns*/named.lock
rm -f ns*/named.memstats
rm -f ns*/*.run
rm -f ns*/*core *core
rm -f ns*/named.conf

rm -f ns2/*.local
rm -f ns2/*.queries
rm -f ns2/named.[0-9]*.conf
rm -f ns2/named.conf.header

rm -f ns3/named.conf
rm -f ns3/named.run.prev

rm -f dnsrps*.conf dnsrpzd*
rm -f ns*/session.key
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
