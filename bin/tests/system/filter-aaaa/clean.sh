#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ns1/K*
rm -f ns1/*.signed
rm -f ns1/signer.err
rm -f ns1/dsset-*

rm -f */named.run
rm -f */named.conf
rm -f */named.memstats

rm -f ns4/K*
rm -f ns4/*.signed
rm -f ns4/signer.err
rm -f ns4/dsset-*

rm -f dig.out.*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*

rm -f ns*/trusted.conf
rm -f ns*/keygen.out
