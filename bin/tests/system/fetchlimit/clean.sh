#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f */named.conf */named.memstats */ans.run */named.recursing */named.run
rm -f dig.out*
rm -f ans4/norespond
rm -f ns3/named.stats ns3/named_dump.db
rm -f burst.input.*
rm -f ns*/managed-keys.bind*
