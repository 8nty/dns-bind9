#!/usr/local/bin/perl -w

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

$0 =~ s%.*/%%;

if (@ARGV != 0) {
	warn "Usage: $0 < list-of-files\n";
	warn "The util/copyrights file is normally used for list-of-files.\n";
	exit(1);
}

$total = 0;

printf "Lines Trimmed:\n";

while (defined($line = <STDIN>)) {
	($file) = split(/\s+/, $line, 2);

        # These are binary and must be ignored.
        next if $file =~ m%/random.data|\.gif$%;
        next if -B $file;

        print "$file\n";

	unless (open(FILEIN, "< $file")) {
		warn "$0: open < $file: $!, skipping\n";
		next;
	}
        
	undef $/;		# Slurp whole file.
	$_ = <FILEIN>;
	$/ = "\n";		# Back to line-at-a-time for <FILES>.

        close(FILEIN);

	$count = s/[ \t]+$//mg;

	next unless $count > 0;

	unless (open(FILEOUT, "> $file")) {
		warn "$0: open > $file: $!, skipping\n";
		next;
	}

	print FILEOUT or die "$0: printing to $file: $!, exiting\n";
        close FILEOUT or die "$0: closing $file: $!, exiting\n";

	printf("%6d lines trimmed in $file\n", $count) if $count > 0;

	$total += $count;
}

printf "%6d TOTAL\n", $total;

exit(0);

