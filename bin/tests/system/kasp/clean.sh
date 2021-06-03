#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ./keygen.*
rm -f ./K*.private ./K*.key ./K*.state ./K*.cmp
rm -rf ./keys/
rm -f dig.out* rrsig.out.* keyevent.out.*
rm -f ns*/named.conf ns*/named.memstats ns*/named.run*
rm -f ns*/policies/*.conf
rm -f ns*/*.jnl ns*/*.jbk
rm -f ns*/K*.private ns*/K*.key ns*/K*.state
rm -f ns*/dsset-* ns*/*.db ns*/*.db.signed
rm -f ns*/keygen.out.* ns*/settime.out.* ns*/signer.out.*
rm -f ns*/managed-keys.bind
rm -f ns*/*.mkeys
rm -f ns*/zones ns*/*.db.infile
rm -f ns*/*.zsk1 ns*/*.zsk2
rm -f ns3/legacy-keys.*
rm -f *.created published.test* retired.test*
rm -f rndc.dnssec.*.out.*
rm -f python.out.*
rm -f *-supported.file
rm -f created.key-* unused.key-*
