#!/usr/bin/env perl

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

use strict;
use warnings;

print "#pragma once\n";
print "#define TRUST_ANCHORS \"\\\n";

my $fn = shift or die "Usage: $0 FILENAME\n";
open(my $fh, '<', $fn) or die "cannot open file $ARGV[1]\n";
while (<$fh>) {
    chomp;
    s/\"/\\\"/g;
    print $_ . "\\n\\\n";
}
close($fh);
print "\"\n";
