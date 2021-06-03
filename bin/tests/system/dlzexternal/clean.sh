#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after dlzexternal tests.
#

rm -f ns1/update.txt
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f ns1/ddns.key
rm -f dig.out*
rm -f ns*/named.lock
rm -f ns1/session.key
rm -f ns*/managed-keys.bind*
