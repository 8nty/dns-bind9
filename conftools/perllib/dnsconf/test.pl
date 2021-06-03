#!/usr/bin/perl

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

push(@ARGV, "/etc/named.conf") if ! @ARGV;

use DNSConf;

##
## First get the current named.conf file and print it.
##
$named = new DNSConf;

$named->parse($ARGV[0]);

$dir = $named->getdirectory();

print "the directory value in $ARGV[0] is: ";
if (!defined($dir)) {
    print "undefined\n";
} else {
    print $dir, "\n";
}

print "\n\nAnd the full file is:\n\n";
$named->print(STDOUT);



##
## Now create out own and fill it up.
##

$anothernamed = new DNSConf;

$thedir = "/var/tmp";

print "Created a virgin config structure and added \"$thedir\"\n";
print "as the directory\n";

$anothernamed->setdirectory($thedir);

$anothernamed->settransfersin(300);

$str = $anothernamed->getdirectory();
print "Pulling that value out again yields: \"", $str, "\"\n";

print "And the full file contents is: \n\n";
$anothernamed->print(STDOUT);

undef($named);
undef($anothernamed);
