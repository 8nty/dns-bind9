#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after zone transfer tests.
#

rm -f ./*/named.conf
rm -f ./*/named.memstats
rm -f ./*/named.run
rm -f ./*/named.run.prev
rm -f ./dig.out.*
rm -f ./*/example.db
