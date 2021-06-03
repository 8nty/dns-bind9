#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../conf.sh

set -e

$SHELL clean.sh

copy_setports ns3/named.conf.in ns3/named.conf
copy_setports ns4/named.conf.in ns4/named.conf

copy_setports ns3/kasp.conf.in ns3/kasp.conf

# Setup zones
(
	cd ns3
	$SHELL setup.sh
)
(
	cd ns4
	$SHELL setup.sh
)
