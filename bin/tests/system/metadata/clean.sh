#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f K* dsset-* *.signed *.new
rm -f zsk.key ksk.key parent.ksk.key parent.zsk.key 
rm -f pending.key rolling.key standby.key inact.key
rm -f prerev.key postrev.key oldstyle.key
rm -f keys sigs
rm -f tmp.out
rm -f settime1.test* settime2.test*
rm -f ns*/named.lock
