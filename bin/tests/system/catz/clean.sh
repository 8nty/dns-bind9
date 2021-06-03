# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

rm -f dig.out.*
rm -f ns*/*.jnl
rm -f ns*/*.nzf
rm -f ns*/named.lock
rm -f ns*/named.memstats
rm -f ns*/named.conf
rm -f ns*/named.run
rm -f ns*/named.run.prev
rm -f ns1/*dom*example.db
rm -f ns2/__catz__*db
rm -f ns2/named.conf.tmp
rm -f ns3/dom13.example.db ns3/dom14.example.db
rm -f nsupdate.out.*
rm -f ns[123]/catalog[1234].example.db
rm -rf ns2/zonedir
rm -f ns*/*.nzd ns*/*.nzd-lock
rm -f ns*/managed-keys.bind*
rm -f wait_for_message.*
