#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

if ! $FEATURETEST --with-dlz-filesystem; then
        echo_i "DLZ filesystem driver not supported"
        exit 255
fi
exit 0
