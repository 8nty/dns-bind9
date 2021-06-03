#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

$SHELL clean.sh

(cd ns6 && $SHELL -e sign.sh)
(cd ns7 && $SHELL -e sign.sh)

$SHELL clean.sh
