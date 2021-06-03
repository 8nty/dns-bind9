#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after tsiggss tests.
#

rm -f ns1/*.jnl ns1/update.txt ns1/auth.sock
rm -f ns1/*.db ns1/K*.key ns1/K*.private
rm -f ns1/_default.tsigkeys
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f authsock.pid
rm -f ns1/core
rm -f nsupdate.out*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
