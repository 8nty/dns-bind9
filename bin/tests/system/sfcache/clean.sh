#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ./*/K*.key ./*/K*.private ./*/*.signed ./*/*.db ./*/dsset-*
rm -f ./*/managed.conf ./*/trusted.conf
rm -f ./*/named.memstats
rm -f ./*/named.conf
rm -f ./*/named.run ./*/named.run.prev
rm -f ./dig.*
rm -f ./rndc.*
rm -f ./sfcache.*
rm -f ./ns*/managed-keys.bind*
rm -f ./ns*/named.lock
rm -f ./ns5/named.run.part*
rm -f ./ns5/named_dump*
