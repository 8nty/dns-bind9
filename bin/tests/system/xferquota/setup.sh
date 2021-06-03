#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Set up test data for zone transfer quota tests.
#

. ../conf.sh

$PERL setup.pl

cp -f ns1/changing1.db ns1/changing.db

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
