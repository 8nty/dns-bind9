#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$FEATURETEST --tsan && {
	echo_i "TSAN - skipping dlzexternal test"
        exit 255
}

exit 0
