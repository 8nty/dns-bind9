#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

# NOTE: The number of signing keys generated below is not coincidental.  More
# details can be found in the comment inside ns7/named.conf.

zone=nsec3-loop
rm -f K${zone}.+*+*.key
rm -f K${zone}.+*+*.private
keyname=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone $zone`
keyname=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone $zone`
keyname=`$KEYGEN -q -a NSEC3RSASHA1 -b 1024 -n zone -f KSK $zone`
