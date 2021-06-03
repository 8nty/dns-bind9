#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
# server-xml.pl:
# Parses the XML version of the server stats into a normalized format.

use XML::Simple;

my $ref = XMLin("xml.stats");
my $counters = $ref->{server}->{counters};
foreach $group (@$counters) {
    foreach $key (keys %{$group->{counter}}) {
        print $group->{type} . " " . $key . ": ". $group->{counter}->{$key}->{content} . "\n";
    }
}
