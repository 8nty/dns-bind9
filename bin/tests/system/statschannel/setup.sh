#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# shellcheck source=conf.sh
. ../conf.sh

for conf in ns*/named.conf.in; do
    copy_setports "$conf" "$(dirname "$conf")/$(basename "$conf" .in)"
done

(cd ns2 && $SHELL sign.sh)
