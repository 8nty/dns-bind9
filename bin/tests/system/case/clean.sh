#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f dig.ns*.test*
rm -f ns*/named.conf
rm -f ns*/named.lock
rm -f ns*/named.memstats
rm -f ns*/named.run
rm -f ns1/dynamic.db
rm -f ns1/dynamic.db.jnl
rm -f ns2/dynamic.bk
rm -f ns2/dynamic.bk.jnl
rm -f ns2/example.bk
rm -f ns*/managed-keys.bind*
