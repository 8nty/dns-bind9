#!/usr/bin/perl

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

use strict;

die "Usage: makenames.pl <num> [<len>]" if (@ARGV == 0 || @ARGV > 2);
my $len = 10;
$len = @ARGV[1] if (@ARGV == 2);

my @chars = split("", "abcdefghijklmnopqrstuvwxyz123456789");

srand; 
for (my $i = 0; $i < @ARGV[0]; $i++) {
        my $name = "";
        for (my $j = 0; $j < $len; $j++) {
                my $r = rand 35;
                $name .= $chars[$r];
        }
        print "$name" . ".example\n";
}
