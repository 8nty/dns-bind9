#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
zonefile=root.db

keyname=`$KEYGEN -a rsasha256 -qfk $zone`
zskkeyname=`$KEYGEN -a rsasha256 -q $zone`

$SIGNER -Sg -o $zone $zonefile > /dev/null 2>/dev/null

# Configure the resolving server with an initializing key.
keyfile_to_initial_ds $keyname > managed.conf
cp managed.conf ../ns2/managed.conf
cp managed.conf ../ns4/managed.conf
cp managed.conf ../ns5/managed.conf

# Configure a static key to be used by delv.
keyfile_to_static_ds $keyname > trusted.conf

# Prepare an unsupported algorithm key.
unsupportedkey=Kunknown.+255+00000
cp unsupported.key "${unsupportedkey}.key"

#
#  Save keyname and keyid for managed key id test.
#
echo "$keyname" > managed.key
echo "$zskkeyname" > zone.key
keyfile_to_key_id $keyname > managed.key.id
