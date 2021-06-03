# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

. ../conf.sh

copy_setports ns1/named.conf.in ns1/named.conf
copy_setports ns2/named.conf.in ns2/named.conf
copy_setports ns3/named.conf.in ns3/named.conf
copy_setports ns4/named.conf.in ns4/named.conf

$SHELL ${TOP_SRCDIR}/bin/tests/system/genzone.sh 2 4 | sed -e 's/^$TTL 3600$/$TTL 0 ; force TTL to zero/' -e 's/86400.IN SOA/0 SOA/' > ns2/example.db
