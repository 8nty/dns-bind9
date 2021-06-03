#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ns*/K*.private ns*/K*.key ns*/K*.state
rm -f ns*/named.conf ns*/kasp.conf
rm -f ns*/named.memstats ns*/named.run
rm -f ns*/keygen.out* ns*/signer.out*
rm -f ns*/zones
rm -f ns*/dsset-*
rm -f ns*/*.db ns*/*.db.jnl ns*/*.db.jbk
rm -f ns*/*.db.signed* ns*/*.db.infile
rm -f ns*/managed-keys.bind*
rm -f ns*/*.mkeys*
rm -f ./*.created
rm -f ./created.key-*
rm -f ./dig.out*
rm -f ./python.out.*
rm -f ./retired.*
rm -f ./rndc.dnssec.*
rm -f ./unused.key*

