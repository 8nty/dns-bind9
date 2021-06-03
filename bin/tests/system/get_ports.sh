#!/bin/sh

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
# This script is a 'port' broker.  It keeps track of ports given to the
# individual system subtests, so every test is given a unique port range.

total_tests=$(find . -maxdepth 1 -mindepth 1 -type d | wc -l)
ports_per_test=20

port_min=5001
port_max=$((32767 - (total_tests * ports_per_test)))

baseport=0
test_index=0
while getopts "p:t:-:" OPT; do
    if [ "$OPT" = "-" ] && [ -n "$OPTARG" ]; then
	OPT="${OPTARG%%=*}"
	OPTARG="${OPTARG#$OPT}"
	OPTARG="${OPTARG#=}"
    fi

    # shellcheck disable=SC2214
    case "$OPT" in
	p | port) baseport=$OPTARG ;;
	t | test)
		test_index=$(find . -maxdepth 1 -mindepth 1 -type d | sort | grep -F -x -n "./${OPTARG}" | cut -d: -f1)
		if [ -z "${test_index}" ]; then
			echo "Test '${OPTARG}' not found" >&2
			exit 1
		fi
		;;
	-) break ;;
	*) echo "invalid option" >&2; exit 1 ;;
    esac
done

port_pool_size=$((port_max - port_min))
if [ "${baseport}" -eq 0 ]; then
	baseport="$((($(date +%s) / 3600 % port_pool_size) + port_min + (test_index * ports_per_test)))"
fi

echo "export PORT=$((baseport))"
echo "export TLSPORT=$((baseport + 1))"
echo "export HTTPPORT=$((baseport + 2))"
echo "export HTTPSPORT=$((baseport + 3))"
echo "export EXTRAPORT1=$((baseport + 4))"
echo "export EXTRAPORT2=$((baseport + 5))"
echo "export EXTRAPORT3=$((baseport + 6))"
echo "export EXTRAPORT4=$((baseport + 7))"
echo "export EXTRAPORT5=$((baseport + 8))"
echo "export EXTRAPORT6=$((baseport + 9))"
echo "export EXTRAPORT7=$((baseport + 10))"
echo "export EXTRAPORT8=$((baseport + 11))"
echo "export CONTROLPORT=$((baseport + 12))"

# Local Variables:
# sh-basic-offset: 4
# End:
