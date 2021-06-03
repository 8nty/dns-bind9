#!/usr/bin/perl
#
# SPDX-License-Identifier: MPL-2.0
use strict;
use warnings;

my $target = shift;
my $notbefore;
my $inception;
while (<>) {
	$notbefore = $1 if m{^.* must not be signed before \d+ [(](\d+)[)]};
	$inception = $1 if m{^.* inception time \d+ [(](\d+)[)]};
}
die "missing notbefore time" unless $notbefore;
die "missing inception time" unless $inception;
my $delta = $inception - $notbefore;
die "bad inception time $delta" unless abs($delta - $target) < 3;
