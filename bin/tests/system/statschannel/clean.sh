#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f compressed.headers regular.headers compressed.out regular.out
rm -f dig.out*
rm -f ns*/managed-keys.bind*
rm -f ns*/named.conf
rm -f ns*/named.lock
rm -f ns*/named.memstats
rm -f ns*/named.run*
rm -f ns*/named.stats
rm -f ns*/signzone.out.*
rm -f ns2/*.db.signed* ns2/dsset-*. ns2/*.jbk
rm -f ns2/Kdnssec* ns2/dnssec.*.id
rm -f ns2/Kmanykeys* ns2/manykeys.*.id
rm -f ns2/dnssec.db.signed* ns2/dsset-dnssec.
rm -f ns3/*.db
rm -f traffic traffic.out.* traffic.json.* traffic.xml.*
rm -f xml.*mem json.*mem
rm -f xml.*stats json.*stats
rm -f zones zones.out.* zones.json.* zones.xml.* zones.expect.*
rm -rf ./__pycache__
