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

(
	cd ns3
	$SHELL setup.sh
)
