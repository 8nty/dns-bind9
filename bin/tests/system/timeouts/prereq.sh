#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

if test -n "$PYTHON"
then
    if $PYTHON -c "from dns.query import send_tcp" 2> /dev/null
    then
        :
    else
        echo_i "This test requires the dnspython >= 2.0.0 module." >&2
        exit 1
    fi
else
    echo_i "This test requires Python and the dnspython module." >&2
    exit 1
fi

exit 0
