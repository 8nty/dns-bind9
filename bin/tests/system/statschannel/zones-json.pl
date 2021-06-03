#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
# zones-json.pl:
# Parses the JSON version of the dnssec sign stats for the
# "dnssec" zone in the default view into a normalized format.

use JSON;

my $file = $ARGV[0];
my $zone = $ARGV[1];
open(INPUT, "<$file");
my $text = do{local$/;<INPUT>};
close(INPUT);

my $ref = decode_json($text);


my $dnssecsign = $ref->{views}->{_default}->{zones}[$zone]->{"dnssec-sign"};
my $type = "dnssec-sign operations ";
foreach $key (keys %{$dnssecsign}) {
    print $type . $key . ": ". $dnssecsign->{$key} ."\n";
}
my $dnssecrefresh = $ref->{views}->{_default}->{zones}[$zone]->{"dnssec-refresh"};
my $type = "dnssec-refresh operations ";
foreach $key (keys %{$dnssecrefresh}) {
    print $type . $key . ": ". $dnssecrefresh->{$key} ."\n";
}
