#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
my $target = shift;
my $file = shift;
my $mtime = time - (stat $file)[9];
die "bad mtime $mtime"
	unless ($mtime - $target >= 0 && $mtime - $target < 60);
