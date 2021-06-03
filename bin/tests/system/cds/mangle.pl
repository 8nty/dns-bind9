#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
my $re = $ARGV[0];
shift;
while (<>) {
	s{($re)........}{${1}00000000};
	print;
}
