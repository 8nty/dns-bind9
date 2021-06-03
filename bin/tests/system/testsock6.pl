#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
require 5.001;

use IO::Socket::INET6;

foreach $addr (@ARGV) {
	my $sock;
	$sock = IO::Socket::INET6->new(LocalAddr => $addr,
                                       LocalPort => 0,
                                       Proto     => tcp)
                             or die "Can't bind : $@\n";
	close($sock);
}
