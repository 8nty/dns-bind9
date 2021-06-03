#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f reload.pid

rm -f ns?/zones.conf
rm -f ns?/zone*.bk

rm -f ns1/delegations.db

rm -f ns2/zone0*.db
rm -f ns2/zone0*.jnl
rm -f */named.memstats
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
