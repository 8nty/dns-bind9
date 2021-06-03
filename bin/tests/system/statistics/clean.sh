#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after zone transfer tests.
#

rm -f ns3/example.bk
rm -f ns3/internal.bk
rm -f */named.conf
rm -f */named.memstats
rm -f */named.run
rm -f */ans.run
rm -f */named.stats
rm -f dig.out*
rm -f curl.out.*
rm -f ns*/named.lock
rm -f stats*out
rm -f ns*/managed-keys.bind*
rm -f xsltproc.out.*
