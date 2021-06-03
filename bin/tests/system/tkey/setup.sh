#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

. ../conf.sh

copy_setports ns1/named.conf.in ns1/named.conf

cd ns1 && $SHELL setup.sh
