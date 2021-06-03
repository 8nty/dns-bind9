#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

rm -f K* ns1/K* keyset-* dsset-* ns1/*.db ns1/*.signed ns1/*.jnl
rm -f dig.out* pin upd.log* upd.cmd* pkcs11-list.out*
rm -f ns1/*.ksk ns1/*.zsk ns1/named.memstats
rm -f supported
rm -f ns*/named.run ns*/named.lock ns*/named.conf
rm -f ns*/managed-keys.bind*
