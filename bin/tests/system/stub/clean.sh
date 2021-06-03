#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after stub tests.
#
rm -f dig.out.ns[35] ns3/child.example.st
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
rm -f ns5/example.db
