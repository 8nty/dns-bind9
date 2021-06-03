#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

copy_setports ns1/named.conf.in ns1/named.conf

#
# Generate a large enough zone, so the transfer takes longer than
# tcp-initial-timeout interval
#
$PYTHON -c "
for a in range(150000):
    print('%s IN NS a' % (a))
    print('%s IN NS b' % (a))" > ns1/large.db
