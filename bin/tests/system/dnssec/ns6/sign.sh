#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

set -e

echo_i "ns6/sign.sh"

zone=optout-tld
infile=optout-tld.db.in
zonefile=optout-tld.db

keyname=$("$KEYGEN" -q -a "$DEFAULT_ALGORITHM" -b "$DEFAULT_BITS" -n zone "$zone")

cat "$infile" "$keyname.key" > "$zonefile"

"$SIGNER" -P -3 - -A -o "$zone" "$zonefile" > /dev/null 2>&1
