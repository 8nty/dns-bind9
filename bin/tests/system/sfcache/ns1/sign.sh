#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

set -e

zone=.
infile=root.db.in
zonefile=root.db

(cd ../ns2 && $SHELL sign.sh )

cp "../ns2/dsset-example$TP" .

keyname=$($KEYGEN -q -a "${DEFAULT_ALGORITHM}" -b "${DEFAULT_BITS}" -n zone $zone)

cat "$infile" "$keyname.key" > "$zonefile"

$SIGNER -P -g -o $zone $zonefile > /dev/null

# Configure the resolving server with a static key.
keyfile_to_static_ds "$keyname" > trusted.conf
cp trusted.conf ../ns2/trusted.conf

# ...or with an initializing key.
keyfile_to_initial_ds "$keyname" > managed.conf
