#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

#
# Clean up after zone transfer tests.
#

rm -f ns*/named.conf
rm -f ns3/example.bk dig.out.ns?.?
rm -f ns2/example.db ns3/internal.bk
rm -f -- */*.jnl
rm -f -- */named.memstats
rm -f -- */named.run */named.run.prev
rm -f ns2/external/K*
rm -f ns2/external/inline.db.jbk
rm -f ns2/external/inline.db.signed
rm -f ns2/external/inline.db.signed.jnl
rm -f ns2/internal/K*
rm -f ns2/internal/inline.db.jbk
rm -f ns2/internal/inline.db.signed
rm -f ns2/internal/inline.db.signed.jnl
rm -f ns2/zones.conf
rm -f ns2/db.* ns2/K*
rm -f dig.out.external dig.out.internal
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
