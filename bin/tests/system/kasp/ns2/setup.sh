#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../../conf.sh

echo_i "ns2/setup.sh"

zone="secondary.kasp"
echo_i "setting up zone: $zone"
zonefile="${zone}.db"
infile="${zonefile}.in"
cp $infile $zonefile

zone="signed.tld"
echo_i "setting up zone: $zone"
zonefile="${zone}.db"
infile="template.tld.db.in"
cp $infile $zonefile

zone="unsigned.tld"
echo_i "setting up zone: $zone"
zonefile="${zone}.db"
infile="template.tld.db.in"
cp $infile $zonefile
