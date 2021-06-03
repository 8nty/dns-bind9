#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$FEATURETEST --have-geoip2 || {
	echo_i "This test requires GeoIP support." >&2
	exit 255
}
exit 0
