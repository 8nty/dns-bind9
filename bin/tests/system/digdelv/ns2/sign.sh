#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

set -e

ksk=$("$KEYGEN" -q -a "$DEFAULT_ALGORITHM" -b "$DEFAULT_BITS" -n zone example.)

cp example.db.in example.db

"$SIGNER" -Sz -f example.db -o example example.db.in > /dev/null 2>&1

keyfile_to_key_id "$ksk" > keyid
grep -Ev '^;' < "$ksk.key" | cut -f 7- -d ' ' > keydata

keyfile_to_initial_keys "$ksk" > ../ns3/anchor.dnskey
keyfile_to_initial_ds "$ksk" > ../ns3/anchor.ds
