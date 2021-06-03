#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ./K*
rm -f ./dig.out.*
rm -f ./rndc.out.*
rm -f ns*/K*
rm -f ns*/_default.tsigkeys
rm -f ns*/managed-keys.bind*
rm -f ns*/named.conf
rm -f ns*/named.conf-e
rm -f ns*/named.lock
rm -f ns*/named.memstats
rm -f ns*/named.run
