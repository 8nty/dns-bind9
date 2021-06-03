#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after system tests.
#

. ./conf.sh


find . -type f \( \
    -name '*~' -o -name 'core' -o -name '*.core' \
    -o -name '*.log' -o -name '*.pid' -o -name '*.keyset' \
    -o -name named.run -o -name ans.run \
    -o -name '*-valgrind-*.log' \) -print | xargs rm -f

status=0

rm -f ../random.data

for d in $SUBDIRS
do
   test ! -f $d/clean.sh || ( cd $d && $SHELL clean.sh )
   rm -f test.output.$d
   test -d $d && find $d -type d -exec rmdir '{}' \; 2> /dev/null
done
