#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$SHELL clean.sh

copy_setports ns2/named1.conf.in ns2/named.conf

for i in 1 2 3 4 5 6 7 other bogus; do
        cp ns2/example.db.in ns2/example${i}.db
        echo "@ IN TXT \"$i\"" >> ns2/example$i.db
done
