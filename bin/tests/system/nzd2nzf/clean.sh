#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ./*/named.conf
rm -f ./*/named.run
rm -f ./*/named.memstats
rm -f dig.out.*
rm -f rndc.out*
rm -f ns*/*.nzf
rm -f ns*/*.nzd ns*/*.nzd-lock
rm -f ns*/managed-keys.bind*
