# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

expand "$1" |
awk -v file="$1" 'length > 80 {
    if (logged == 0) {
        print file ": Line Too Long"
        logged = 1
    }
    print
}
END {
    if (logged == 1) {
        exit(1)
    }
}'
