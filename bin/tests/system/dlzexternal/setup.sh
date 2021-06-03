#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$TSIGKEYGEN ddns-key.example.nil > ns1/ddns.key

copy_setports ns1/named.conf.in ns1/named.conf
