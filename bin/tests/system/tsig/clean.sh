#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after tsig tests.
#

rm -f dig.out.*
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f ns*/named.lock
rm -f Kexample.net.*
rm -f keygen.out?
rm -f ns*/managed-keys.bind*
rm -f packet.out
