#!/usr/bin/perl
# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

use warnings;
use strict;

if (@ARGV < 1) {
	print STDERR <<'END';
usage:
    perl rst-zoneopt.pl zoneopt_file
END
	exit 1;
}

my $FILE = shift;

open (FH, "<", $FILE) or die "Can't open $FILE";

print <<END;
.. SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
..
.. SPDX-License-Identifier: MPL-2.0

::

END

while (<FH>) {
	if (m{// not.*implemented} || m{// obsolete} ||
	    m{// ancient} || m{// test.*only})
	{
		next;
	}

	s{ // not configured}{};
	s{ // may occur multiple times}{};
	s{[[]}{[}g;
	s{[]]}{]}g;
	s{        }{\t}g;

	print "  " . $_;
}
