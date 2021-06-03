#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
[ -d ns2/nope ] && chmod 755 ns2/nope

rm -f *.pid
rm -f */named*.run
rm -f */named.memstats
rm -f kill*.out
rm -f ns*/managed-keys.bind*
rm -f ns*/named.lock ns*/named*.pid ns*/other.lock
rm -f ns2/named.conf ns2/named-alt*.conf
rm -f rndc.out*
rm -rf ns2/nope
rm -rf ns2/tmp.*
