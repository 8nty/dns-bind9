#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f dig.out.* rndc.signing.*
rm -f ns*/named.conf ns*/named.memstats ns*/named.run*
rm -f ns*/*.jnl ns*/*.jbk ns*/managed-keys.bind
rm -f ns*/K*.private ns*/K*.key ns*/K*.state
rm -f ns*/dsset-* ns*/*.db ns*/*.db.signed

