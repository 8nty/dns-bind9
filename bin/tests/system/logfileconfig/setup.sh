#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$SHELL clean.sh

copy_setports ns1/named.plain ns1/named.conf
copy_setports ns1/rndc.conf.in ns1/rndc.conf
copy_setports ns1/controls.conf.in ns1/controls.conf
