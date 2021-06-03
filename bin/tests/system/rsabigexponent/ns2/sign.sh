#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=example.
infile=example.db.in
outfile=example.db.bad

for i in Xexample.+005+51829.key Xexample.+005+51829.private \
	Xexample.+005+05896.key Xexample.+005+05896.private
do
	cp $i `echo $i | sed s/X/K/`
done

$SIGNER -g -s 20000101000000 -e 20361231235959 -o $zone \
	$infile Kexample.+005+51829 Kexample.+005+51829 \
	> /dev/null 2> signer.err || true
