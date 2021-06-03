#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
# server-xml.pl:
# Parses the XML version of the server stats into a normalized format.

use XML::Simple;
use Data::Dumper;

my $ref = XMLin("xml.mem");
print Dumper($ref);
