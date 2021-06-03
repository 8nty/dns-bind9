#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f dig.out.ns?.test*
rm -f */dsset-*
rm -f */named.conf
rm -f */named.memstats
rm -f */named.run
rm -f */trusted.conf
rm -f ns1/K.*
rm -f ns1/root.db
rm -f ns1/root.db.signed
rm -f ns2/Kexample.*
rm -f ns2/example.db
rm -f ns2/example.db.signed
rm -f ns*/managed-keys.bind*
