#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

. ../../conf.sh

keyname=$($KEYGEN -T KEY -a DH -b 768 -n host server)
keyid=$(keyfile_to_key_id "$keyname")
sed -i -e "s;KEYID;$keyid;" named.conf
