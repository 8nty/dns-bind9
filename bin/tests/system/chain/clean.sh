#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f dig.out.* named*.pid
rm -f ns*/named.conf
rm -f */named.memstats */named.recursing */named.lock */named.run */ans.run
rm -f ns2/K* ns2/dsset-* ns2/example.db.signed
rm -f ns*/managed-keys.bind*
