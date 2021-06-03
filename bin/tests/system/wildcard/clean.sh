#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ns*/named.run
rm -f ns*/named.conf
rm -f ns1/K*
rm -f ns1/*.db
rm -f ns1/*.signed
rm -f ns1/dsset-*
rm -f ns1/keyset-*
rm -f ns1/trusted.conf
rm -f ns1/private.nsec.conf
rm -f ns1/private.nsec3.conf
rm -f ns1/signer.err
rm -f */named.memstats
rm -f dig.out.ns*.test*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
