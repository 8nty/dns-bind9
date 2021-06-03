#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
# traffic-xml.pl:
# Parses the XML version of the RSSAC002 traffic stats into a
# normalized format.

use XML::Simple;

my $file = $ARGV[0];

my $ref = XMLin($file);

my $udp = $ref->{traffic}->{ipv4}->{udp}->{counters};
foreach $group (@$udp) {
    my $type = "udp " . $group->{type} . " ";
    if (exists $group->{counter}->{name}) {
        print $type . $group->{counter}->{name} . ": " . $group->{counter}->{content} . "\n";
    } else {
        foreach $key (keys %{$group->{counter}}) {
            print $type . $key . ": ". $group->{counter}->{$key}->{content} ."\n";
        }
    }
}

my $tcp = $ref->{traffic}->{ipv4}->{tcp}->{counters};
foreach $group (@$tcp) {
    my $type = "tcp " . $group->{type} . " ";
    if (exists $group->{counter}->{name}) {
        print $type . $group->{counter}->{name} . ": " . $group->{counter}->{content} . "\n";
    } else {
        foreach $key (keys %{$group->{counter}}) {
            print $type . $key . ": ". $group->{counter}->{$key}->{content} ."\n";
        }
    }
}
