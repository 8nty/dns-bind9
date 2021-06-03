#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

rm -f ./dig.out.*
rm -f ./*/named.conf
rm -f ./*/named.memstats
rm -f ./*/named.run
rm -f ./ns*/named.lock
rm -f ./ns*/_default.nzf
rm -f ./ns*/_default.nzd*
rm -f ./ns*/managed-keys.bind* ns*/*.mkeys*
