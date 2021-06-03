# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# Clean up after forward tests.
#
rm -f ./dig.out.*
rm -f ./*/named.conf
rm -f ./*/named.memstats
rm -f ./*/named.run ./*/named.run.prev
rm -f ./ns*/named.lock
rm -f ./ns*/managed-keys.bind*
rm -f ./ns1/root.db ./ns1/root.db.signed
rm -f ./ns*/trusted.conf
rm -f ./ns1/K* ./ns1/dsset-*
