#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after allow query tests.
#

rm -f dig.out.*
rm -f ns*/named.conf
rm -f */named.memstats
rm -f ns*/named.lock
rm -f ns*/named.run ns*/named.run.prev
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
