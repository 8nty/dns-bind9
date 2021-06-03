#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

echo_i "ns3/setup.sh"

setup() {
	zone="$1"
	echo_i "setting up zone: $zone"
	zonefile="${zone}.db"
	infile="${zone}.db.infile"
	cp template.db.in "$zonefile"
}

for zn in nsec-to-nsec3 nsec3 nsec3-other nsec3-change nsec3-to-nsec \
	  nsec3-to-optout nsec3-from-optout nsec3-dynamic nsec3-dynamic-change
do
	setup "${zn}.kasp"
done
