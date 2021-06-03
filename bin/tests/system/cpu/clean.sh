#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f ps.out
rm -f ns1/named.conf ns1/managed-keys.* ns1/named.run ns1/named.memstats
