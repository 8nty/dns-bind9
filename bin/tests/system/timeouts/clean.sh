#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f ./ns*/managed-keys.bind*
rm -f ./ns*/named.conf
rm -f ./ns*/named.lock
rm -f ./ns*/named.memstats
rm -f ./ns*/named.run*
rm -f ./ns*/named.stats
rm -rf ./__pycache__
rm -f ./ns*/large.db
