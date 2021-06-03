#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
rm -f */named.conf
rm -f */named.memstats
rm -f */named.run
rm -f */named.run.prev
rm -f */named.stats
rm -f dig.out*
rm -f dnstap.out dnstap.hex
rm -f dnstap.out.save
rm -f fstrm_capture.out
rm -f ns*/dnstap.out
rm -f ns*/dnstap.out.save
rm -f ns*/dnstap.out.save.?
rm -f ns*/managed-keys.bind*
rm -f ns*/named.lock
rm -f ns2/dnstap.out.*
rm -f ns2/example.db ns2/example.db.jnl
rm -f ns3/dnstap.out.*
rm -f ydump.out
