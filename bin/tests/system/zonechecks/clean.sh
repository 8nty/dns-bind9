#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f *.out
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f */*.db */*.db.signed */K*.key */K*.private */*.jnl */dsset-*
rm -f */signer.err
rm -f rndc.out.*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
