#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f dig.out.test*
rm -f dig.out.cyclic dig.out.fixed dig.out.random dig.out.nomatch dig.out.none
rm -f dig.out.0 dig.out.1 dig.out.2 dig.out.3
rm -f dig.out.cyclic2
rm -f ns2/root.bk
rm -f ns?/named.run ns?/named.core
rm -f */named.memstats
rm -f ns*/named.lock
rm -f ns*/named.conf
rm -f ns*/managed-keys.bind*
