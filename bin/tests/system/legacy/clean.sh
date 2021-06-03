# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

rm -f dig.out.*
rm -f ns*/named.conf
rm -f ns*/named.memstats
rm -f ns*/named.run
rm -f ns*/named.lock

# build.sh
rm -f ns1/named_dump.db*
rm -f ns6/K*
rm -f ns6/dsset-*
rm -f ns6/edns512.db
rm -f ns6/signer.err
rm -f ns7/K*
rm -f ns7/dsset-*
rm -f ns7/edns512-notcp.db
rm -f ns7/signer.err
rm -f ns7/trusted.conf
rm -f ns*/managed-keys.bind*
