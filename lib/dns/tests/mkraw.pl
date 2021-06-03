#!/usr/bin/perl -w

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

use strict;
chomp(my $line = <STDIN>);
print pack("H*", $line);
