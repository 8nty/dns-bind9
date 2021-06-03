#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

list1=$(
	grep LOGCATEGORY lib/*/include/*/*.h bin/named/include/named/*.h |
	grep "#define.*(&" |
	sed -e 's/.*LOGCATEGORY_\([A-Z_]*\).*/\1/' -e 's/^RRL$/rate-limit/' |
	tr '[A-Z]' '[a-z]' |
	tr _ - |
	sed 's/^tat$/trust-anchor-telemetry/' |
	sort -u
)
list2=$(
	sed -ne 's/^``\(.*\)``/\1/p' doc/arm/logging-categories.rst |
	sort -u
)
status=0
for i in $list1
do
	ok=no
	for j in $list2
	do
		if test $i = $j
		then
			ok=yes
		fi
	done
	if test $ok = no
	then
		echo "$i missing from documentation."
		status=1
	fi
done
for i in $list2
do
	ok=no
	for j in $list1
	do
		if test $i = $j
		then
			ok=yes
		fi
	done
	if test $ok = no
	then
		echo "$i not in code."
		status=1
	fi
done
exit $status
