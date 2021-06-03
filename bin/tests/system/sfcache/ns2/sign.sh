#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

set -e

zone=example.
infile=example.db.in
zonefile=example.db

keyname1=$("$KEYGEN" -q -a "$DEFAULT_ALGORITHM" -b "$DEFAULT_BITS" -n zone "$zone")
keyname2=$("$KEYGEN" -q -a "$DEFAULT_ALGORITHM" -b "$DEFAULT_BITS" -n zone "$zone")

cat "$infile" "$keyname1.key" "$keyname2.key" > "$zonefile"

"$SIGNER" -P -g -o "$zone" -k "$keyname1" "$zonefile" "$keyname2" > /dev/null
