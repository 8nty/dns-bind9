#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

zone=example
infile=example.db.in
zonefile=example.db

keyname=$($KEYGEN -q -a RSASHA256 -b 2048 -n zone $zone)
cat "$infile" "$keyname.key" > "$zonefile"

$SIGNER -P -o $zone $zonefile > /dev/null

zone=dnamed
infile=dnamed.db.in
zonefile=dnamed.db

keyname=$($KEYGEN -q -a RSASHA256 -b 2048 -n zone $zone)
cat "$infile" "$keyname.key" > "$zonefile"

$SIGNER -P -o $zone $zonefile > /dev/null

zone=.
infile=root.db.in
zonefile=root.db

keyname=$($KEYGEN -q -a ${DEFAULT_ALGORITHM} -b ${DEFAULT_BITS} -n zone $zone)
cat "$infile" "$keyname.key" > "$zonefile"

$SIGNER -P -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a static key.
keyfile_to_static_ds "$keyname" > trusted.conf
