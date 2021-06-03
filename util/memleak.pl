#!/usr/bin/perl

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

$mem_stats = '';

while (<>) {
    $gets{$1.$2} = $_ if (/add (?:0x)?([0-9a-f]+) size (?:0x)?([0-9]+) file/);
    delete $gets{$1.$2} if /del (?:0x)?([0-9a-f]+) size (?:0x)?([0-9]+) file/;
    $mem_stats .= $_ if /\d+ gets, +(\d+) rem/ && $1 > 0;
}
print join('', values %gets);
print $mem_stats;

exit(0);
