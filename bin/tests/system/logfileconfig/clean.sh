#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
#
# Clean up after log file tests
#
rm -f ns1/rndc.conf
rm -f ns1/controls.conf
rm -f ns1/named.conf
rm -f ns1/named.pid ns1/named.run
rm -f ns1/named.memstats ns1/dig.out
rm -f ns1/named_log ns1/named_pipe ns1/named_sym
rm -rf ns1/named_dir
rm -f ns1/named_deflog
rm -f ns*/named.lock
rm -f ns1/query_log
rm -f ns1/named_iso8601
rm -f ns1/named_iso8601_utc
rm -f ns1/rndc.out.test*
rm -f ns1/dig.out.test*
rm -f ns1/named_vers
rm -f ns1/named_vers.*
rm -f ns1/named_ts
rm -f ns1/named_ts.*
rm -f ns1/named_unlimited
rm -f ns1/named_unlimited.*
rm -f ns*/managed-keys.bind*
