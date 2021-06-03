#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../../conf.sh

zone=.
zonefile=root.db

# an RSA key
rsakey=`$KEYGEN -a rsasha256 -qfk rsasha256.`

# a key with unsupported algorithm
unsupportedkey=Kunknown.+255+00000
cp unsupported-managed.key "${unsupportedkey}.key"

# root key
rootkey=`cat ../ns1/managed.key`
cp "../ns1/${rootkey}.key" .

# Configure the resolving server with an initializing key.
# (We use key-format trust anchors here because otherwise the
# unsupported algorithm test won't work.)
keyfile_to_initial_keys $unsupportedkey $rsakey $rootkey > managed.conf
