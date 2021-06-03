#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ns*/named.conf
rm -f ns1/K*
rm -f ns1/signed.db*
rm -f ns1/dsset-signed.
rm -f */named.memstats
rm -f */named.run
rm -f dig.out.*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
