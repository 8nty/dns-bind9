#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after dyndb tests.
#
rm -f */named.conf
rm -f */named.run
rm -f ns1/named.memstats
rm -f ns1/update.txt
rm -f added.a.out.*
rm -f added.ptr.out.*
rm -f deleted.a.out.*
rm -f deleted.ptr.out.*
rm -f ns*/managed-keys.bind*
