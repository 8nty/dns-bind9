#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=example
rm -f K${zone}.+*+*.key
rm -f K${zone}.+*+*.private
keyname=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone $zone`
keyname=`$KEYGEN -q -a RSASHA1 -b 1024 -n zone -f KSK $zone`
