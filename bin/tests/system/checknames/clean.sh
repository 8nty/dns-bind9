#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ns*/named.conf
rm -f dig.out.ns?.test*
rm -f nsupdate.out.test*
rm -f ns1/*.example.db
rm -f ns1/*.update.db
rm -f ns1/*.update.db.jnl
rm -f ns4/*.update.db
rm -f ns4/*.update.db.jnl
rm -f */named.memstats
rm -f */named.run
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
