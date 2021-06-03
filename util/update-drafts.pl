#!/usr/local/bin/perl -w

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

foreach (@ARGV) {
    $ofile = $_;
    if (/^(.*-)([0-9][0-9])(\.txt)/) {
	    $nfile = "$1" . sprintf("%02d", $2 + 1) . "$3";
	    print $nfile, "\n";
	    system "ftp http://www.ietf.org/internet-drafts/$nfile";
	    if ($? == 0) {
		unlink($ofile);
		system "cvs remove $ofile";
		system "cvs add $nfile";
	    }
    }
}
