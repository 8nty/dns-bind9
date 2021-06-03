#!/bin/sh -e

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

copy_setports ../common/controls.conf.in ns2/controls.conf
copy_setports  ns1/named.conf.in ns1/named.conf
copy_setports  ns2/named01.conf.in ns2/named.conf
copy_setports  ns3/named1.conf.in ns3/named.conf
