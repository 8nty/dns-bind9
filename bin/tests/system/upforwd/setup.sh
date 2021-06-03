#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

cp -f ns1/example1.db ns1/example.db
cp -f ns3/nomaster.db ns3/nomaster1.db

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
copy_setports ns3/named.conf.in ns3/named.conf

if $FEATURETEST --enable-dnstap
then
	cat <<'EOF' > ns3/dnstap.conf
	dnstap-identity "ns3";
	dnstap-version "xxx";
	dnstap-output file "dnstap.out";
	dnstap { all; };
EOF
else
	echo "/* DNSTAP NOT ENABLED */" >ns3/dnstap.conf
fi


#
# SIG(0) required cryptographic support which may not be configured.
#
keyname=`$KEYGEN  -q -n HOST -a RSASHA1 -b 1024 -T KEY sig0.example2 2>keyname.err`
if test -n "$keyname"
then
	cat ns1/example1.db $keyname.key > ns1/example2.db
	echo $keyname > keyname
else
	cat ns1/example1.db > ns1/example2.db
fi
cat_i < keyname.err
