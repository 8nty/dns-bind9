#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$SHELL clean.sh

$SHELL ${TOP_SRCDIR}/bin/tests/system/genzone.sh 1 >ns1/example.db

copy_setports ns1/named.conf.in ns1/named.conf
