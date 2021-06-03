#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

copy_setports ns1/named1.conf.in ns1/named.conf
copy_setports ns2/named1.conf.in ns2/named.conf
copy_setports ns3/named1.conf.in ns3/named.conf
copy_setports ns4/named1.conf.in ns4/named.conf
copy_setports ns5/named.conf.in ns5/named.conf

(cd ns1 && $SHELL -e sign.sh)
(cd ns4 && $SHELL -e sign.sh)
