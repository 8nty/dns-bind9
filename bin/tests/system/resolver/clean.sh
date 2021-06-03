#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after resolver tests.
#
rm -f */named.conf
rm -f */named.memstats
rm -f */named.run
rm -f */ans.run
rm -f */*.jdb
rm -f dig.out dig.out.* dig.*.out.*
rm -f dig.*.foo.*
rm -f dig.*.bar.*
rm -f dig.*.prime.*
rm -f ns4/tld.db
rm -f ns6/K*
rm -f ns6/example.net.db.signed ns6/example.net.db
rm -f ns6/ds.example.net.db.signed ns6/ds.example.net.db
rm -f ns6/dsset-ds.example.net*
rm -f ns6/dsset-example.net* ns6/example.net.db.signed.jnl
rm -f ns6/named.stats*
rm -f ns6/to-be-removed.tld.db ns6/to-be-removed.tld.db.jnl
rm -f ns7/server.db ns7/server.db.jnl
rm -f resolve.out.*.test*
rm -f .digrc
rm -f ns*/named.lock
rm -f ns5/trusted.conf
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
