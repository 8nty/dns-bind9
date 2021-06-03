#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f dig.out check.out
rm -f */named.memstats
rm -f */named.conf
rm -f */named.run
rm -f */*.bk
rm -f */*.bk.*
rm -f ns3/Kexample.*
rm -f ns*/named.lock
rm -f ns*/managed-keys.bind* ns*/*.mkeys*
