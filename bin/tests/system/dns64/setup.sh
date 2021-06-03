#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

copy_setports ns1/named.conf1.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf

cd ns1 && $SHELL sign.sh
