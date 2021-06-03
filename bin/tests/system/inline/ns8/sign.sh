#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

for zone in example01.com example02.com example03.com example04.com \
	    example05.com example06.com example07.com example08.com \
	    example09.com example10.com example11.com example12.com \
	    example13.com example14.com example15.com example16.com
do
  rm -f K${zone}.+*+*.key
  rm -f K${zone}.+*+*.private
  keyname=`$KEYGEN -q -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS -n zone $zone`
  keyname=`$KEYGEN -q -a $DEFAULT_ALGORITHM -b $DEFAULT_BITS -n zone -f KSK $zone`
  cp example.com.db.in ${zone}.db
  $SIGNER -S -T 3600 -O raw -o ${zone} ${zone}.db > /dev/null 2>&1
done
