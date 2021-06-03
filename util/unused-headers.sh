#!/bin/bash

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

unused_headers=$(
	git ls-files -- '*.h' ':!:*include*' ':!:*rdata*' ':!:*win32*' |
	sed 's|.*/\(.*\.h\)|\1|' |
	while read -r header; do
		git grep -q "#include \".*${header}\"" || echo "${header}"
	done

	git ls-files -- '*include/*.h' |
	sed 's|.*/include\/\(.*\.h\)|\1|' |
	while read -r header; do
		git grep -q "#include <${header}>" || echo "${header}"
	done
)

if [ -n "${unused_headers}" ]; then
	echo -e "Following headers are unused:\n${unused_headers}"
	exit 1
fi
