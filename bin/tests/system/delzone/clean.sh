#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f dig.out.*
rm -f rndc.out*
rm -f */named.memstats
rm -f ns2/*.nzf
rm -f ns2/*.nzd ns2/*nzd-lock
rm -f ns2/core*
rm -f ns2/inline.db.jbk
rm -f ns2/inline.db.signed
rm -f ns2/inlinesec.bk*
rm -f ns*/named.lock
rm -f ns2/nzf-*
rm -f ns*/managed-keys.bind*
