#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
#
# Send a file to a given address and port using TCP.  Used for
# configuring the test server in ans.pl.
#

use IO::File;
use IO::Socket;

@ARGV == 2 or die "usage: send.pl host port [file ...]\n";

my $host = shift @ARGV;
my $port = shift @ARGV;

my $sock = IO::Socket::INET->new(PeerAddr => $host, PeerPort => $port,
				 Proto => "tcp",) or die "$!";
while (<>) {
	$sock->syswrite($_, length $_);
}

$sock->close;
