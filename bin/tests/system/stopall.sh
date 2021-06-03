#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Stop all hanging processes from any system tests.
#

. ./conf.sh

for d in $SUBDIRS
do
   $SHELL stop.sh $d
done
