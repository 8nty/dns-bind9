#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f good.conf.in good.conf.out badzero.conf *.out
rm -f good-kasp.conf.in
rm -rf test.keydir
rm -f checkconf.out*
rm -f diff.out*
rm -f ns*/named.lock
