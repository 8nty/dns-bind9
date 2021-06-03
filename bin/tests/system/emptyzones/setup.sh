# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

. ../conf.sh

$SHELL clean.sh
copy_setports ns1/named1.conf.in ns1/named.conf
