#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
# Converts hex ascii into raw data.
# (This can be used, for example, to construct input for "wire_data -d".)

require 5.006.001;

use strict;
use IO::File;

sub usage {
    print ("Usage: packet.pl [file]\n");
    exit 1;
}

my $file = "STDIN";
if (@ARGV >= 1) {
    my $filename = shift @ARGV;
    open FH, "<$filename" or die "$filename: $!";
    $file = "FH";
}

my $input = "";
while (defined(my $line = <$file>) ) {
    chomp $line;
    $line =~ s/#.*$//;
    $input .= $line;
}

$input =~ s/\s+//g;
my $data = pack("H*", $input);
my $len = length $data;

binmode(STDOUT);
print($data);
exit(0);
