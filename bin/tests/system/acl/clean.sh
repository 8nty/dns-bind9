#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after zone transfer tests.
#

rm -f dig.out.*
rm -f ns2/example.db ns2/tsigzone.db ns2/example.db.jnl
rm -f */named.conf
rm -f */named.memstats
rm -f */named.run
rm -f ns*/named.lock
rm -f ns*/_default.nzf
rm -f ns*/_default.nzd*
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
