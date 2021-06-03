#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

. ../conf.sh

if $SHELL ../testcrypto.sh ecdsap384sha384; then
	echo "yes" > ecdsa256-supported.file
fi

if $SHELL ../testcrypto.sh ecdsap384sha384; then
	echo "yes" > ecdsa384-supported.file
fi

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
copy_setports ns3/named.conf.in ns3/named.conf
(
	cd ns1
	$SHELL sign.sh
)
