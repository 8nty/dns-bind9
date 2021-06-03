#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -rf */*.signed
rm -rf */*.jnl
rm -rf */K*
rm -rf */dsset-*
rm -rf */named.memstats
rm -rf */named.run
rm -rf */trusted.conf
rm -rf ns1/root.db
rm -rf ns2/example.db
rm -rf ns2/example.com.db
rm -rf nsupdate.out.test
rm -f ns*/named.lock
rm -f ns*/named.conf
rm -f ns*/managed-keys.bind*
