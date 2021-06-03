#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ./conf.sh

[ -x "$TOP_BUILDDIR/bin/pkcs11/pkcs11-destroy" ] && $PK11DEL -w0 > /dev/null 2>&1
