#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

SYSTESTDIR=filter-aaaa

zone=signed.
infile=signed.db.in
zonefile=signed.db.signed
outfile=signed.db.signed

$KEYGEN -a $DEFAULT_ALGORITHM $zone 2>&1 > /dev/null | cat_i
$KEYGEN -f KSK -a $DEFAULT_ALGORITHM $zone 2>&1 > /dev/null | cat_i

$SIGNER -S -o $zone -f $outfile $infile > /dev/null 2> signer.err || cat signer.err
echo_i "signed zone '$zone'"
