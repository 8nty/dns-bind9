#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

copy_setports ns1/named1.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
copy_setports ns3/named.conf.in ns3/named.conf
copy_setports ns4/named.conf.in ns4/named.conf
copy_setports ns5/named.conf.in ns5/named.conf
copy_setports ns6/named.conf.in ns6/named.conf
copy_setports ns7/named.conf.in ns7/named.conf

cp ns5/named1.args ns5/named.args

( cd ns1 && $SHELL sign.sh )
( cd ns6 && $SHELL setup.sh )

cp ns2/managed.conf ns2/managed1.conf

cd ns4
mkdir nope
touch nope/managed-keys.bind
touch nope/managed.keys.bind.jnl
chmod 444 nope/*
