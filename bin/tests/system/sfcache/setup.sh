#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../conf.sh

set -e

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
copy_setports ns5/named.conf.in ns5/named.conf

cd ns1 && $SHELL sign.sh && cd ..
cd ns5 && $SHELL sign.sh && cd ..
