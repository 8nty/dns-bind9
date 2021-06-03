#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

# enable the tsiggss test only if gssapi was enabled
$FEATURETEST --gssapi ||  {
        echo_i "gssapi and krb5 not supported - skipping tsiggss test"
        exit 255
}

exit 0
