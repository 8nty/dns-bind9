#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ./dig.out*
rm -f ns*/*.signed
rm -f ns*/K*
rm -f ns*/dsset-*
rm -f ns*/managed-keys.bind*
rm -f ns*/named.conf
rm -f ns*/named.lock
rm -f ns*/named.memstats
rm -f ns*/named.run
rm -f ns*/root.db
rm -f ns*/signer.err
rm -f ns*/trusted.conf
rm -f ns*/example.com.db
rm -f *-supported.file
