#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f */named.conf
rm -f */named.memstats
rm -f */named.run
rm -f */named.stats
rm -f dig.out.*
rm -f ns*/named.lock
rm -f ns1/K*
rm -f ns1/dsset-nsec3.
rm -f ns1/dsset-signed.
rm -f ns1/nsec3.db*
rm -f ns1/signed.db*
rm -f ns2/*.db
rm -f ns3/K*
rm -f ns3/dsset-nsec3.
rm -f ns3/dsset-signed.
rm -f ns3/nsec3.db*
rm -f ns3/signed.db*
rm -f ns4/*.db
rm -f ns5/dsset-*
rm -f ns5/K* ns5/sign.ns5.*
rm -f ns5/root.db ns5/root.db.signed
rm -f ns5/signed.db ns5/signed.db.signed
rm -f ns6/signed.db.signed
rm -f rndc.out
rm -f ns*/managed-keys.bind*
