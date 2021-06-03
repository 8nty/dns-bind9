#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f K* */K* */dsset-*. */*.signed */trusted.conf */tmp*
rm -f ns*/dsset-example
rm -f ns*/named.run
rm -f ns*/named.memstats
rm -f ns1/root.db
rm -f ns2/signer.err
rm -f dig.out.*
rm -f ns*/named.lock
rm -f ns*/named.conf
rm -f ns*/managed-keys.bind*
