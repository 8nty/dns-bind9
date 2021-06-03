#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
. ../conf.sh

status=0

echo_i "test name too long"
$PERL formerr.pl -a 10.53.0.1 -p ${PORT} nametoolong > nametoolong.out
ans=`grep got: nametoolong.out`
if [ "${ans}" != "got: 000080010000000000000000" ];
then
	echo_i "failed"; status=`expr $status + 1`;
fi

echo_i "two questions"
$PERL formerr.pl -a 10.53.0.1 -p ${PORT} twoquestions > twoquestions.out
ans=`grep got: twoquestions.out`
if [ "${ans}" != "got: 000080010000000000000000" ];
then
	echo_i "failed"; status=`expr $status + 1`;
fi

# this would be NOERROR if it included a COOKIE option,
# but is a FORMERR without one.
echo_i "empty question section (and no COOKIE option)"
$PERL formerr.pl -a 10.53.0.1 -p ${PORT} noquestions > noquestions.out
ans=`grep got: noquestions.out`
if [ "${ans}" != "got: 000080010000000000000000" ];
then
	echo_i "failed"; status=`expr $status + 1`;
fi

echo_i "exit status: $status"

[ $status -eq 0 ] || exit 1
