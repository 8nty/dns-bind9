#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

echo_i "ns4/setup.sh"

private_type_record() {
	_zone=$1
	_algorithm=$2
	_keyfile=$3

	_id=$(keyfile_to_key_id "$_keyfile")

	printf "%s. 0 IN TYPE65534 %s 5 %02x%04x0000\n" "$_zone" "\\#" "$_algorithm" "$_id"
}

# Make lines shorter by storing key states in environment variables.
H="HIDDEN"
R="RUMOURED"
O="OMNIPRESENT"
U="UNRETENTIVE"

zone="view-rsasha256.kasp"
algo="RSASHA256"
num="8"
echo "$zone" >> zones

# Set up zones in views with auto-dnssec maintain to migrate to dnssec-policy.
# The keys for these zones are in use long enough that they should start a
# rollover for the ZSK (P3M), but not long enough to initiate a KSK rollover (P1Y).
ksktimes="-P -186d -A -186d -P sync -186d"
zsktimes="-P -186d -A -186d"
KSK=$($KEYGEN -a $algo -L 300 -b 2048 -f KSK $ksktimes $zone 2> keygen.out.$zone.1)
ZSK=$($KEYGEN -a $algo -L 300 -b 1024        $zsktimes $zone 2> keygen.out.$zone.2)

echo_i "setting up zone $zone (external)"
view="ext"
zonefile="${zone}.${view}.db"
cat template.$view.db.in "${KSK}.key" "${ZSK}.key" > "$zonefile"

echo_i "setting up zone $zone (internal)"
view="int"
zonefile="${zone}.${view}.db"
cat template.$view.db.in "${KSK}.key" "${ZSK}.key" > "$zonefile"
