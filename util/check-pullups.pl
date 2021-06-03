#!/usr/bin/perl

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

use FileHandle;

# $/ = "";

# Read the CHANGES file $fn and return a hash of change
# texts and categories indexed by change number.

sub readfile {
	my ($fn) = @_;
	my $fh = new FileHandle($fn, "r")
	    or die "open: $fn: $!";
	
	my $changes = { };

	my ($changeid, $category);

	$changeid = "none";
	$category = "none";

	while (<$fh>) {
		if (m/^\s*(\d+)\.\s+\[(\w+)\]/) {
			$changeid = $1;
			$category = $2;
			# print "*** $1 $2\n";
		} elsif (m/---.* released ---/) {
			$changeid = "none";
			$category = "none";
			next;
		} elsif (m/^# /) {
			$changeid = "none";
			$category = "none";
			next;
		}
		if ($changeid eq "none") {
			next;
		}
		$changes->{$changeid}->{text} .= $_;
		$changes->{$changeid}->{category} = $category;
	}

	return $changes;
}

@ARGV == 2 || @ARGV == 3 or die "usage: $0 changes-file-1 changes-file-2\n";

my $c1 = readfile($ARGV[0]);
my $c2 = readfile($ARGV[1]);
if (@ARGV == 3) {
	$c3 = readfile($ARGV[2]);
} else {
	my $c3 = { };
}

my $msg = "";
foreach my $c (sort {$a <=> $b} keys %$c1) {
	my $category = $c1->{$c}->{category};
	my $text = $c1->{$c}->{text};
	if ($category ne "func" && $category ne "placeholder" &&
	    !exists($c2->{$c}) && !exists($c3->{$c})) {
		if ($msg ne "MISSING\n") {
			$msg = "MISSING\n";
			print $msg;
		}
		print $c1->{$c}->{text};
	}
	if (exists($c2->{$c}) && $category ne "placeholder" &&
	    $c2->{$c}->{text} ne $text && !exists($c3->{$c})) {
		if ($msg ne "TEXT\n") {
			$msg = "TEXT\n";
			print $msg;
		}
		print $c2->{$c}->{text};
		print $c1->{$c}->{text};
	}
}
