#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
set -e

. ../conf.sh

supported=0
if $SHELL ../testcrypto.sh ed25519; then
	supported=1
fi
if $SHELL ../testcrypto.sh ed448; then
	supported=1
fi

[ "$supported" -eq 1 ] || exit 1
