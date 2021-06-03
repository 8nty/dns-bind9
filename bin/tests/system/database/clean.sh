#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ns1/named.conf ns1/named.run ns1/named.memstats
rm -f dig.out.*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
