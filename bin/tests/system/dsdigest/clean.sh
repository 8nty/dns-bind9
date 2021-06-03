#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f supported
rm -f */K* */dsset-* */*.signed */trusted.conf
rm -f ns1/root.db
rm -f ns1/signer.err
rm -f ns2/good.db ns2/bad.db
rm -f dig.out*
rm -f */named.conf
rm -f */named.run
rm -f */named.memstats
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind*
