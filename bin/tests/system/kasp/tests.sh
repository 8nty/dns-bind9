#!/bin/sh
#
# Copyright (C) Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# See the COPYRIGHT file distributed with this work for additional
# information regarding copyright ownership.

# shellcheck source=conf.sh
SYSTEMTESTTOP=..
. "$SYSTEMTESTTOP/conf.sh"

status=0
n=0

###############################################################################
# Constants                                                                   #
###############################################################################
DEFAULT_TTL=300

###############################################################################
# Key properties                                                              #
###############################################################################
ID=0
EXPECT=1
ROLE=2
KSK=3
ZSK=4
LIFETIME=5
ALG_NUM=6
ALG_STR=7
ALG_LEN=8
PUBLISHED=9
ACTIVE=10
RETIRED=11
REVOKED=12
REMOVED=13
GOAL=14
STATE_DNSKEY=15
STATE_ZRRSIG=16
STATE_KRRSIG=17
STATE_DS=18
EXPECT_RRSIG=19

# Clear key state.
#
# This will update either the KEY1, KEY2, or KEY3 array.
key_clear() {
	_key=(	[$ID]="no" [$EXPECT]="no" \
		[$ROLE]="none" [$KSK]="no" [$ZSK]="no" \
		[$LIFETIME]="0" [$ALG_NUM]="0" \
		[$ALG_STR]="none" [$ALG_LEN]="0" \
		[$PUBLISHED]="none" [$ACTIVE]="none" \
		[$RETIRED]="none" [$REVOKED]="none" \
		[$REMOVED]="none" \
		[$GOAL]="none" [$STATE_DNSKEY]="none" \
		[$STATE_KRRSIG]="none" [$STATE_ZRRSIG]="none" \
		[$STATE_DS]="none" [$EXPECT_RRSIG]="no")

	if [ $1 == "KEY1" ]; then
		KEY1=(${_key[*]})
	elif [ $1 == "KEY2" ]; then
		KEY2=(${_key[*]})
	elif [ $1 == "KEY3" ]; then
		KEY3=(${_key[*]})
	fi
}

# Start clear.
key_clear "KEY1"
key_clear "KEY2"
key_clear "KEY3"

###############################################################################
# Utilities                                                                   #
###############################################################################

# Call dig with default options.
dig_with_opts() {
	"$DIG" +tcp +noadd +nosea +nostat +nocmd +dnssec -p "$PORT" "$@"
}

# Print IDs of keys used for generating RRSIG records for RRsets of type $1
# found in dig output file $2.
get_keys_which_signed() {
	_qtype=$1
	_output=$2
	# The key ID is the 11th column of the RRSIG record line.
	awk -v qt="$_qtype" '$4 == "RRSIG" && $5 == qt {print $11}' < "$_output"
}

# Get the key ids from key files for zone $2 in directory $1
# that matches algorithm $3.
get_keyids() {
	_dir=$1
	_zone=$2
	_algorithm=$(printf "%03d" $3)
	_start="${_dir}/K${_zone}.+${_algorithm}+"
	_end=".key"

	ls ${_start}*${_end} | sed "s/$_dir\/K${_zone}.+${_algorithm}+\([0-9]\{5\}\)${_end}/\1/"
}

# By default log errors and don't quit immediately.
_log=1
log_error() {
	test $_log -eq 1 && echo_i "error: $1"
	ret=$((ret+1))
}

# TODO: Move wait_for_log to conf.sh.common
wait_for_log() {
	_msg=$1
	_file=$2

	for i in 1 2 3 4 5 6 7 8 9 10; do
		nextpart "$_file" | grep "$_msg" > /dev/null && return
		sleep 1
	done
	log_error "exceeded time limit waiting for '$_msg' in $_file"
}

# Set zone properties for testing keys.
# $1: Key directory
# $2: Zone name
# $3: Policy name
# $4: DNSKEY TTL
# $5: Number of keys
#
# This will set the following environment variables for testing:
# DIR, ZONE, POLICY, DNSKEY_TTL, NUM_KEYS
zone_properties() {
	DIR=$1
	ZONE=$2
	POLICY=$3
	DNSKEY_TTL=$4
	NUM_KEYS=$5
}

# Set key properties for testing keys.
# $1: Key to update
# $2: Role
# $3: Lifetime
# $4: Algorithm (number)
# $5: Algorithm (string-format)
# $6: Algorithm length
# $7: Is signing
#
# This will update either the KEY1, KEY2 or KEY3 array.
key_properties() {
	if [ $1 == "KEY1" ]; then
		KEY1[$EXPECT]="yes"
		KEY1[$ROLE]=$2
		KEY1[$KSK]="no"
		KEY1[$ZSK]="no"
		test $2 == "ksk" && KEY1[$KSK]="yes"
		test $2 == "zsk" && KEY1[$ZSK]="yes"
		test $2 == "csk" && KEY1[$KSK]="yes"
		test $2 == "csk" && KEY1[$ZSK]="yes"
		KEY1[$LIFETIME]=$3
		KEY1[$ALG_NUM]=$4
		KEY1[$ALG_STR]=$5
		KEY1[$ALG_LEN]=$6
		KEY1[$EXPECT_RRSIG]=$7
	elif [ $1 == "KEY2" ]; then
		KEY2[$EXPECT]="yes"
		KEY2[$ROLE]=$2
		KEY2[$KSK]="no"
		KEY2[$ZSK]="no"
		test $2 == "ksk" && KEY2[$KSK]="yes"
		test $2 == "zsk" && KEY2[$ZSK]="yes"
		test $2 == "csk" && KEY2[$KSK]="yes"
		test $2 == "csk" && KEY2[$ZSK]="yes"
		KEY2[$LIFETIME]=$3
		KEY2[$ALG_NUM]=$4
		KEY2[$ALG_STR]=$5
		KEY2[$ALG_LEN]=$6
		KEY2[$EXPECT_RRSIG]=$7
	elif [ $1 == "KEY3" ]; then
		KEY3[$EXPECT]="yes"
		KEY3[$ROLE]=$2
		KEY3[$KSK]="no"
		KEY3[$ZSK]="no"
		test $2 == "ksk" && KEY3[$KSK]="yes"
		test $2 == "zsk" && KEY3[$ZSK]="yes"
		test $2 == "csk" && KEY3[$KSK]="yes"
		test $2 == "csk" && KEY3[$ZSK]="yes"
		KEY3[$LIFETIME]=$3
		KEY3[$ALG_NUM]=$4
		KEY3[$ALG_STR]=$5
		KEY3[$ALG_LEN]=$6
		KEY3[$EXPECT_RRSIG]=$7
	fi
}

# Set key timing metadata. Set to "none" to unset.
# These times are hard to test, so it is just an indication that we expect the
# respective timing metadata in the key files.
# $1: Key to update
# $2: Published
# $3: Active
# $4: Retired
# $5: Revoked
# $6: Removed
#
# This will update either the KEY1, KEY2 or KEY3 array.
key_timings() {
	if [ $1 == "KEY1" ]; then
		KEY1[$EXPECT]="yes"
		KEY1[$PUBLISHED]=$2
		KEY1[$ACTIVE]=$3
		KEY1[$RETIRED]=$4
		KEY1[$REVOKED]=$5
		KEY1[$REMOVED]=$6
	elif [ $1 == "KEY2" ]; then
		KEY2[$EXPECT]="yes"
		KEY2[$PUBLISHED]=$2
		KEY2[$ACTIVE]=$3
		KEY2[$RETIRED]=$4
		KEY2[$REVOKED]=$5
		KEY2[$REMOVED]=$6
	elif [ $1 == "KEY3" ]; then
		KEY3[$EXPECT]="yes"
		KEY3[$PUBLISHED]=$2
		KEY3[$ACTIVE]=$3
		KEY3[$RETIRED]=$4
		KEY3[$REVOKED]=$5
		KEY3[$REMOVED]=$6
	fi
}

# Set key state metadata. Set to "none" to unset.
# $1: Key to update
# $2: Goal state
# $3: DNSKEY state
# $4: RRSIG state (zsk)
# $5: RRSIG state (ksk)
# $6: DS state
#
# This will update either the KEY1, KEY2, OR KEY3 array.
key_states() {
	if [ $1 == "KEY1" ]; then
		KEY1[$EXPECT]="yes"
		KEY1[$GOAL]=$2
		KEY1[$STATE_DNSKEY]=$3
		KEY1[$STATE_ZRRSIG]=$4
		KEY1[$STATE_KRRSIG]=$5
		KEY1[$STATE_DS]=$6
	elif [ $1 == "KEY2" ]; then
		KEY2[$EXPECT]="yes"
		KEY2[$GOAL]=$2
		KEY2[$STATE_DNSKEY]=$3
		KEY2[$STATE_ZRRSIG]=$4
		KEY2[$STATE_KRRSIG]=$5
		KEY2[$STATE_DS]=$6
	elif [ $1 == "KEY3" ]; then
		KEY3[$EXPECT]="yes"
		KEY3[$GOAL]=$2
		KEY3[$STATE_DNSKEY]=$3
		KEY3[$STATE_ZRRSIG]=$4
		KEY3[$STATE_KRRSIG]=$5
		KEY3[$STATE_DS]=$6
	fi
}

# Check the key $1 with id $2.
# This requires environment variables to be set with 'zone_properties',
# 'key_properties', 'key_timings', and 'key_states'.
#
# This will set the following environment variables for testing:
# BASE_FILE="${_dir}/K${_zone}.+${_alg_numpad}+${_key_idpad}"
# KEY_FILE="${BASE_FILE}.key"
# PRIVATE_FILE="${BASE_FILE}.private"
# STATE_FILE="${BASE_FILE}.state"
# KEY_ID=$(echo $1 | sed 's/^0*//')
check_key() {
	if [ $1 == "KEY1" ]; then
		_key=(${KEY1[*]})
	elif [ $1 == "KEY2" ]; then
		_key=(${KEY2[*]})
	elif [ $1 == "KEY3" ]; then
		_key=(${KEY3[*]})
	fi

	_dir=$DIR
	_zone=$ZONE
	_role="${_key[$ROLE]}"
	_key_idpad=$2
	_key_id=$(echo $_key_idpad | sed 's/^0*//')
	_alg_num="${_key[$ALG_NUM]}"
        _alg_numpad=$(printf "%03d" $_alg_num)
	_alg_string="${_key[$ALG_STR]}"
	_length="${_key[$ALG_LEN]}"
	_dnskey_ttl=$DNSKEY_TTL
	_lifetime="${_key[$LIFETIME]}"

	_published="${_key[$PUBLISHED]}"
	_active="${_key[$ACTIVE]}"
	_retired="${_key[$RETIRED]}"
	_revoked="${_key[$REVOKED]}"
	_removed="${_key[$REMOVED]}"

	_goal="${_key[$GOAL]}"
	_state_dnskey="${_key[$STATE_DNSKEY]}"
	_state_zrrsig="${_key[$STATE_ZRRSIG]}"
	_state_krrsig="${_key[$STATE_KRRSIG]}"
	_state_ds="${_key[$STATE_DS]}"

	_ksk="no"
	_zsk="no"
	if [ "$_role" == "ksk" ]; then
		_role2="key-signing"
		_ksk="yes"
		_flags="257"
	elif [ "$_role" == "zsk" ]; then
		_role2="zone-signing"
		_zsk="yes"
		_flags="256"
	elif [ "$_role" == "csk" ]; then
		_role2="key-signing"
		_zsk="yes"
		_ksk="yes"
		_flags="257"
	fi

	BASE_FILE="${_dir}/K${_zone}.+${_alg_numpad}+${_key_idpad}"
	KEY_FILE="${BASE_FILE}.key"
	PRIVATE_FILE="${BASE_FILE}.private"
	STATE_FILE="${BASE_FILE}.state"
	KEY_ID="${_key_id}"

	test $_log -eq 1 && echo_i "check key $BASE_FILE"

	# Check the public key file.
	grep "This is a ${_role2} key, keyid ${_key_id}, for ${_zone}." $KEY_FILE > /dev/null || log_error "mismatch top comment in $KEY_FILE"
	grep "${_zone}\. ${_dnskey_ttl} IN DNSKEY ${_flags} 3 ${_alg_num}" $KEY_FILE > /dev/null || log_error "mismatch DNSKEY record in $KEY_FILE"
	# Now check the private key file.
	grep "Private-key-format: v1.3" $PRIVATE_FILE > /dev/null || log_error "mismatch private key format in $PRIVATE_FILE"
	grep "Algorithm: ${_alg_num} (${_alg_string})" $PRIVATE_FILE > /dev/null || log_error "mismatch algorithm in $PRIVATE_FILE"
	# Now check the key state file.
	grep "This is the state of key ${_key_id}, for ${_zone}." $STATE_FILE > /dev/null || log_error "mismatch top comment in $STATE_FILE"
	grep "Lifetime: ${_lifetime}" $STATE_FILE > /dev/null || log_error "mismatch lifetime in $STATE_FILE"
	grep "Algorithm: ${_alg_num}" $STATE_FILE > /dev/null || log_error "mismatch algorithm in $STATE_FILE"
	grep "Length: ${_length}" $STATE_FILE > /dev/null || log_error "mismatch length in $STATE_FILE"
	grep "KSK: ${_ksk}" $STATE_FILE > /dev/null || log_error "mismatch ksk in $STATE_FILE"
	grep "ZSK: ${_zsk}" $STATE_FILE > /dev/null || log_error "mismatch zsk in $STATE_FILE"

	# Check key states.
	if [ "$_goal" == "none" ]; then
		grep "GoalState: " $STATE_FILE > /dev/null && log_error "unexpected goal state in $STATE_FILE"
	else
		grep "GoalState: ${_goal}" $STATE_FILE > /dev/null || log_error "mismatch goal state in $STATE_FILE"
	fi

	if [ "$_state_dnskey" == "none" ]; then
		grep "DNSKEYState: " $STATE_FILE > /dev/null && log_error "unexpected dnskey state in $STATE_FILE"
		grep "DNSKEYChange: " $STATE_FILE > /dev/null && log_error "unexpected dnskey change in $STATE_FILE"
	else
		grep "DNSKEYState: ${_state_dnskey}" $STATE_FILE > /dev/null || log_error "mismatch dnskey state in $STATE_FILE"
		grep "DNSKEYChange: " $STATE_FILE > /dev/null || log_error "mismatch dnskey change in $STATE_FILE"
	fi

	if [ "$_state_zrrsig" == "none" ]; then
		grep "ZRRSIGState: " $STATE_FILE > /dev/null && log_error "unexpected zrrsig state in $STATE_FILE"
		grep "ZRRSIGChange: " $STATE_FILE > /dev/null && log_error "unexpected zrrsig change in $STATE_FILE"
	else
		grep "ZRRSIGState: ${_state_zrrsig}" $STATE_FILE > /dev/null || log_error "mismatch zrrsig state in $STATE_FILE"
		grep "ZRRSIGChange: " $STATE_FILE > /dev/null || log_error "mismatch zrrsig change in $STATE_FILE"
	fi

	if [ "$_state_krrsig" == "none" ]; then
		grep "KRRSIGState: " $STATE_FILE > /dev/null && log_error "unexpected krrsig state in $STATE_FILE"
		grep "KRRSIGChange: " $STATE_FILE > /dev/null && log_error "unexpected krrsig change in $STATE_FILE"
	else
		grep "KRRSIGState: ${_state_krrsig}" $STATE_FILE > /dev/null || log_error "mismatch krrsig state in $STATE_FILE"
		grep "KRRSIGChange: " $STATE_FILE > /dev/null || log_error "mismatch krrsig change in $STATE_FILE"
	fi

	if [ "$_state_ds" == "none" ]; then
		grep "DSState: " $STATE_FILE > /dev/null && log_error "unexpected ds state in $STATE_FILE"
		grep "DSChange: " $STATE_FILE > /dev/null && log_error "unexpected ds change in $STATE_FILE"
	else
		grep "DSState: ${_state_ds}" $STATE_FILE > /dev/null || log_error "mismatch ds state in $STATE_FILE"
		grep "DSChange: " $STATE_FILE > /dev/null || log_error "mismatch ds change in $STATE_FILE"
	fi

	# Check timing metadata.
	if [ "$_published" == "none" ]; then
		grep "; Publish:" $KEY_FILE > /dev/null && log_error "unexpected publish comment in $KEY_FILE"
		grep "Publish:" $PRIVATE_FILE > /dev/null && log_error "unexpected publish in $PRIVATE_FILE"
		grep "Published: " $STATE_FILE > /dev/null && log_error "unexpected publish in $STATE_FILE"
	else
		grep "; Publish:" $KEY_FILE > /dev/null || log_error "mismatch publish comment in $KEY_FILE ($KEY_PUBLISHED)"
		grep "Publish:" $PRIVATE_FILE > /dev/null || log_error "mismatch publish in $PRIVATE_FILE ($KEY_PUBLISHED)"
		grep "Published:" $STATE_FILE > /dev/null || log_error "mismatch publish in $STATE_FILE ($KEY_PUBLISHED)"
	fi

	if [ "$_active" == "none" ]; then
		grep "; Activate:" $KEY_FILE > /dev/null && log_error "unexpected active comment in $KEY_FILE"
		grep "Activate:" $PRIVATE_FILE > /dev/null && log_error "unexpected active in $PRIVATE_FILE"
		grep "Active: " $STATE_FILE > /dev/null && log_error "unexpected active in $STATE_FILE"
	else
		grep "; Activate:" $KEY_FILE > /dev/null || log_error "mismatch active comment in $KEY_FILE"
		grep "Activate:" $PRIVATE_FILE > /dev/null || log_error "mismatch active in $PRIVATE_FILE"
		grep "Active: " $STATE_FILE > /dev/null || log_error "mismatch active in $STATE_FILE"
	fi

	if [ "$_retired" == "none" ]; then
		grep "; Inactive:" $KEY_FILE > /dev/null && log_error "unexpected retired comment in $KEY_FILE"
		grep "Inactive:" $PRIVATE_FILE > /dev/null && log_error "unexpected retired in $PRIVATE_FILE"
		grep "Retired: " $STATE_FILE > /dev/null && log_error "unexpected retired in $STATE_FILE"
	else
		grep "; Inactive:" $KEY_FILE > /dev/null || log_error "mismatch retired comment in $KEY_FILE"
		grep "Inactive:" $PRIVATE_FILE > /dev/null || log_error "mismatch retired in $PRIVATE_FILE"
		grep "Retired: " $STATE_FILE > /dev/null || log_error "mismatch retired in $STATE_FILE"
	fi

	if [ "$_revoked" == "none" ]; then
		grep "; Revoke:" $KEY_FILE > /dev/null && log_error "unexpected revoked comment in $KEY_FILE"
		grep "Revoke:" $PRIVATE_FILE > /dev/null && log_error "unexpected revoked in $PRIVATE_FILE"
		grep "Revoked: " $STATE_FILE > /dev/null && log_error "unexpected revoked in $STATE_FILE"
	else
		grep "; Revoke:" $KEY_FILE > /dev/null || log_error "mismatch revoked comment in $KEY_FILE"
		grep "Revoke:" $PRIVATE_FILE > /dev/null || log_error "mismatch revoked in $PRIVATE_FILE"
		grep "Revoked: " $STATE_FILE > /dev/null || log_error "mismatch revoked in $STATE_FILE"
	fi

	if [ "$_removed" == "none" ]; then
		grep "; Delete:" $KEY_FILE > /dev/null && log_error "unexpected removed comment in $KEY_FILE"
		grep "Delete:" $PRIVATE_FILE > /dev/null && log_error "unexpected removed in $PRIVATE_FILE"
		grep "Removed: " $STATE_FILE > /dev/null && log_error "unexpected removed in $STATE_FILE"
	else
		grep "; Delete:" $KEY_FILE > /dev/null || log_error "mismatch removed comment in $KEY_FILE"
		grep "Delete:" $PRIVATE_FILE > /dev/null || log_error "mismatch removed in $PRIVATE_FILE"
		grep "Removed: " $STATE_FILE > /dev/null || log_error "mismatch removed in $STATE_FILE"
	fi

	grep "; Created:" $KEY_FILE > /dev/null || log_error "mismatch created comment in $KEY_FILE"
	grep "Created:" $PRIVATE_FILE > /dev/null || log_error "mismatch created in $PRIVATE_FILE"
	grep "Generated: " $STATE_FILE > /dev/null || log_error "mismatch generated in $STATE_FILE"
}

# Check the key with key id $1 and see if it is unused.
# This requires environment variables to be set with 'zone_properties',
# and 'key_properties'.
#
# This will set the following environment variables for testing:
# BASE_FILE="${_dir}/K${_zone}.+${_alg_numpad}+${_key_idpad}"
# KEY_FILE="${BASE_FILE}.key"
# PRIVATE_FILE="${BASE_FILE}.private"
# STATE_FILE="${BASE_FILE}.state"
# KEY_ID=$(echo $1 | sed 's/^0*//')
key_unused() {
	_dir=$DIR
	_zone=$ZONE
	_key_idpad=$1
	_key_id=$(echo $_key_idpad | sed 's/^0*//')
	_alg_num="${KEY1[$ALG_NUM]}"
        _alg_numpad=$(printf "%03d" $_alg_num)

	BASE_FILE="${_dir}/K${_zone}.+${_alg_numpad}+${_key_idpad}"
	KEY_FILE="${BASE_FILE}.key"
	PRIVATE_FILE="${BASE_FILE}.private"
	STATE_FILE="${BASE_FILE}.state"
	KEY_ID="${_key_id}"

	test $_log -eq 1 && echo_i "key unused $KEY_ID?"

	# Check timing metadata.
	grep "; Publish:" $KEY_FILE > /dev/null && log_error "unexpected publish comment in $KEY_FILE"
	grep "Publish:" $PRIVATE_FILE > /dev/null && log_error "unexpected publish in $PRIVATE_FILE"
	grep "Published: " $STATE_FILE > /dev/null && log_error "unexpected publish in $STATE_FILE"
	grep "; Activate:" $KEY_FILE > /dev/null && log_error "unexpected active comment in $KEY_FILE"
	grep "Activate:" $PRIVATE_FILE > /dev/null && log_error "unexpected active in $PRIVATE_FILE"
	grep "Active: " $STATE_FILE > /dev/null && log_error "unexpected active in $STATE_FILE"
	grep "; Inactive:" $KEY_FILE > /dev/null && log_error "unexpected retired comment in $KEY_FILE"
	grep "Inactive:" $PRIVATE_FILE > /dev/null && log_error "unexpected retired in $PRIVATE_FILE"
	grep "Retired: " $STATE_FILE > /dev/null && log_error "unexpected retired in $STATE_FILE"
	grep "; Revoke:" $KEY_FILE > /dev/null && log_error "unexpected revoked comment in $KEY_FILE"
	grep "Revoke:" $PRIVATE_FILE > /dev/null && log_error "unexpected revoked in $PRIVATE_FILE"
	grep "Revoked: " $STATE_FILE > /dev/null && log_error "unexpected revoked in $STATE_FILE"
	grep "; Delete:" $KEY_FILE > /dev/null && log_error "unexpected removed comment in $KEY_FILE"
	grep "Delete:" $PRIVATE_FILE > /dev/null && log_error "unexpected removed in $PRIVATE_FILE"
	grep "Removed: " $STATE_FILE > /dev/null && log_error "unexpected removed in $STATE_FILE"
}

# Test: dnssec-verify zone $1.
dnssec_verify()
{
	n=$((n+1))
	echo_i "dnssec-verify zone ${ZONE} ($n)"
	ret=0
	dig_with_opts $ZONE @10.53.0.3 AXFR > dig.out.axfr.test$n || log_error "dig ${ZONE} AXFR failed"
	$VERIFY -z -o $ZONE dig.out.axfr.test$n > /dev/null || log_error "dnssec verify zone $ZONE failed"
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))
}

###############################################################################
# Tests                                                                       #
###############################################################################

#
# dnssec-keygen
#
zone_properties "keys" "kasp" "kasp" "200"

n=$((n+1))
echo_i "check that 'dnssec-keygen -k' (configured policy) creates valid files ($n)"
ret=0
$KEYGEN -K keys -k $POLICY -l kasp.conf $ZONE > keygen.out.kasp.test$n 2>/dev/null || ret=1
lines=$(cat keygen.out.kasp.test$n | wc -l)
test "$lines" -eq 4 || log_error "wrong number of keys created for policy kasp: $lines"
# Temporarily don't log errors because we are searching multiple files.
_log=0
# Check one algorithm.
key_properties "KEY1" "csk" "31536000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "none" "none" "none" "none" "none"
key_states "KEY1" "none" "none" "none" "none" "none"
id=$(get_keyids $DIR $ZONE "${KEY1[$ALG_NUM]}")
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))
# Check the other algorithm.
key_properties "KEY1" "ksk" "31536000" "8" "RSASHA256" "2048" "yes"
key_timings "KEY1" "none" "none" "none" "none" "none"
key_states "KEY1" "none" "none" "none" "none" "none"

key_properties "KEY2" "zsk" "2592000" "8" "RSASHA256" "1024" "yes"
key_timings "KEY2" "none" "none" "none" "none" "none"
key_states "KEY2" "none" "none" "none" "none" "none"

key_properties "KEY3" "zsk" "16070400" "8" "RSASHA256" "2000" "yes"
key_timings "KEY3" "none" "none" "none" "none" "none"
key_states "KEY3" "none" "none" "none" "none" "none"

ids=$(get_keyids $DIR $ZONE "${KEY1[$ALG_NUM]}")
for id in $ids; do
	# There are three key files with the same algorithm.
	# Check them until a match is found.
	ret=0 && check_key "KEY1" $id
	test "$ret" -eq 0 && continue

	ret=0 && check_key "KEY2" $id
	test "$ret" -eq 0 && continue

	ret=0 && check_key "KEY3" $id
	# If ret is still non-zero, non of the files matched.
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))
done
# Turn error logs on again.
_log=1

n=$((n+1))
echo_i "check that 'dnssec-keygen -k' (default policy) creates valid files ($n)"
ret=0
zone_properties "." "kasp" "_default" "3600"
key_properties "KEY1" "csk" "0" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "none" "none" "none" "none" "none"
key_states "KEY1" "none" "none" "none" "none" "none"
$KEYGEN -k $POLICY $ZONE > keygen.out._default.test$n 2>/dev/null || ret=1
lines=$(cat keygen.out._default.test$n | wc -l)
test "$lines" -eq 1 || log_error "wrong number of keys created for policy _default: $lines"
id=$(get_keyids $DIR $ZONE "${KEY1[$ALG_NUM]}")
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

n=$((n+1))
echo_i "check that 'dnssec-keygen -k' (default policy) creates valid files ($n)"
ret=0
zone_properties "." "kasp" "_default" "3600"
key_properties "KEY1" "csk" "0" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "none" "none" "none" "none" "none"
key_states "KEY1" "none" "none" "none" "none" "none"
$KEYGEN -k $POLICY $ZONE > keygen.out.$POLICY.test$n 2>/dev/null || ret=1
lines=$(cat keygen.out._default.test$n | wc -l)
test "$lines" -eq 1 || log_error "wrong number of keys created for policy _default: $lines"
id=$(get_keyids $DIR $ZONE "${KEY1[$ALG_NUM]}")
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

#
# dnssec-settime
#

# These test builds upon the latest created key with dnssec-keygen and uses the
# environment variables BASE_FILE, KEY_FILE, PRIVATE_FILE and STATE_FILE.
CMP_FILE="${BASE_FILE}.cmp"
n=$((n+1))
echo_i "check that 'dnssec-settime' by default does not edit key state file ($n)"
ret=0
cp $STATE_FILE $CMP_FILE
$SETTIME -P +3600 $BASE_FILE > /dev/null || log_error "settime failed"
grep "; Publish: " $KEY_FILE > /dev/null || log_error "mismatch published in $KEY_FILE"
grep "Publish: " $PRIVATE_FILE > /dev/null || log_error "mismatch published in $PRIVATE_FILE"
$DIFF $CMP_FILE $STATE_FILE || log_error "unexpected file change in $STATE_FILE"
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

n=$((n+1))
echo_i "check that 'dnssec-settime -s' also sets publish time metadata and states in key state file ($n)"
ret=0
cp $STATE_FILE $CMP_FILE
now=$(date +%Y%m%d%H%M%S)
$SETTIME -s -P $now -g "omnipresent" -k "rumoured" $now -z "omnipresent" $now -r "rumoured" $now -d "hidden" $now $BASE_FILE > /dev/null || log_error "settime failed"
key_timings "KEY1" "published" "none" "none" "none" "none"
key_states "KEY1" "omnipresent" "rumoured" "omnipresent" "rumoured" "hidden"
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

n=$((n+1))
echo_i "check that 'dnssec-settime -s' also unsets publish time metadata and states in key state file ($n)"
ret=0
cp $STATE_FILE $CMP_FILE
$SETTIME -s -P "none" -g "none" -k "none" $now -z "none" $now -r "none" $now -d "none" $now $BASE_FILE > /dev/null || log_error "settime failed"
key_timings "KEY1" "none" "none" "none" "none" "none"
key_states "KEY1" "none" "none" "none" "none" "none"
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

n=$((n+1))
echo_i "check that 'dnssec-settime -s' also sets active time metadata and states in key state file (uppercase) ($n)"
ret=0
cp $STATE_FILE $CMP_FILE
now=$(date +%Y%m%d%H%M%S)
$SETTIME -s -A $now -g "HIDDEN" -k "UNRETENTIVE" $now -z "UNRETENTIVE" $now -r "OMNIPRESENT" $now -d "OMNIPRESENT" $now $BASE_FILE > /dev/null || log_error "settime failed"
key_timings "KEY1" "none" "active" "none" "none" "none"
key_states "KEY1" "hidden" "unretentive" "unretentive" "omnipresent" "omnipresent"
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))


#
# named
#
#
#  The NSEC record at the apex of the zone and its RRSIG records are
#  added as part of the last step in signing a zone.  We wait for the
#  NSEC records to appear before proceeding with a counter to prevent
#  infinite loops if there is a error.
#
n=$((n+1))
echo_i "waiting for kasp signing changes to take effect ($n)"
i=0
while [ $i -lt 30 ]
do
	ret=0
	for z in `cat ns3/zones`
	do
		dig_with_opts $z @10.53.0.3 nsec > dig.out.ns3.test$n.$z || ret=1
		grep "NS SOA" dig.out.ns3.test$n.$z > /dev/null || ret=1
		grep "$z\..*IN.*RRSIG" dig.out.ns3.test$n.$z > /dev/null || ret=1
	done
	i=`expr $i + 1`
	if [ $ret = 0 ]; then break; fi
	echo_i "waiting ... ($i)"
	sleep 1
done
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))


#
# Zone: default.kasp.
#

# Check the zone with default kasp policy has loaded and is signed.
zone_properties "ns3" "default.kasp" "_default" "3600"
key_properties "KEY1" "csk" "0" "13" "ECDSAP256SHA256" "256" "yes"
# The first key is immediately published and activated.
key_timings "KEY1" "published" "active" "none" "none" "none" "none"
# DNSKEY, RRSIG (ksk), RRSIG (zsk) are published. DS needs to wait.
key_states "KEY1" "omnipresent" "rumoured" "rumoured" "rumoured" "hidden"

n=$((n+1))
echo_i "check key is created for zone ${ZONE} ($n)"
ret=0
wait_for_log "DNSKEY .* created for policy ${POLICY}" "${DIR}/named.run"
nextpartreset "${DIR}/named.run"
id=$(get_keyids $DIR $ZONE "${KEY1[$ALG_NUM]}")
check_key "KEY1" $id
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

# Verify signed zone.
dnssec_verify $ZONE

# Test DNSKEY query.
qtype="DNSKEY"
n=$((n+1))
echo_i "check ${qtype} rrset is signed correctly for zone ${ZONE} ($n)"
ret=0
dig_with_opts $ZONE @10.53.0.3 $qtype > dig.out.$DIR.test$n || log_error "dig ${ZONE} ${qtype} failed"
grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
grep "${ZONE}\..*${DNSKEY_TTL}.*IN.*${qtype}.*257.*.3.*${KEY1[$ALG_NUM]}" dig.out.$DIR.test$n > /dev/null || log_error "missing ${qtype} record in response"
lines=$(get_keys_which_signed $qtype dig.out.$DIR.test$n | wc -l)
test "$lines" -eq 1 || log_error "bad number ($lines) of RRSIG records in DNS response"
get_keys_which_signed $qtype dig.out.$DIR.test$n | grep "^${KEY_ID}$" > /dev/null || log_error "${qtype} RRset not signed with ${KEY_ID}"
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

# Test SOA query.
qtype="SOA"
n=$((n+1))
echo_i "check ${qtype} rrset is signed correctly for zone ${ZONE} ($n)"
ret=0
dig_with_opts $ZONE @10.53.0.3 $qtype > dig.out.$DIR.test$n || log_error "dig ${ZONE} ${qtype} failed"
grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
grep "${ZONE}\..*${DEFAULT_TTL}.*IN.*${qtype}.*mname1\..*\." dig.out.$DIR.test$n > /dev/null || log_error "missing ${qtype} record in response"
lines=$(get_keys_which_signed $qtype dig.out.$DIR.test$n | wc -l)
test "$lines" -eq 1 || log_error "bad number ($lines) of RRSIG records in DNS response"
get_keys_which_signed $qtype dig.out.$DIR.test$n | grep "^${KEY_ID}$" > /dev/null || log_error "${qtype} RRset not signed with ${KEY_ID}"
test "$ret" -eq 0 || echo_i "failed"
status=$((status+ret))

#
# Zone: rsasha1.kasp.
#
zone_properties "ns3" "rsasha1.kasp" "rsasha1" "1234" "3"
key_properties "KEY1" "ksk" "315360000" "5" "RSASHA1" "2048" "yes"
key_properties "KEY2" "zsk" "157680000" "5" "RSASHA1" "1024" "yes"
key_properties "KEY3" "zsk" "31536000" "5" "RSASHA1" "2000" "yes"
# The first keys are immediately published and activated.
# Because lifetime > 0, retired timing is also set.
key_timings "KEY1" "published" "active" "retired" "none" "none"
key_timings "KEY2" "published" "active" "retired" "none" "none"
key_timings "KEY3" "published" "active" "retired" "none" "none"
# KSK: DNSKEY, RRSIG (ksk) published. DS needs to wait.
# ZSK: DNSKEY, RRSIG (zsk) published.
key_states "KEY1" "omnipresent" "rumoured" "none" "rumoured" "hidden"
key_states "KEY2" "omnipresent" "rumoured" "rumoured" "none" "none"
key_states "KEY3" "omnipresent" "rumoured" "rumoured" "none" "none"

# Check keys for a configured zone. This verifies:
# 1. The right number of keys exist in the key pool ($1).
# 2. The right number of keys is active (always expect three keys).
#    The algorithm expected is set with $2 (string) and $3 (number), and the
#    expected sizes for the keys are set with $4 (ksk), $5 and $6 (zsk).
#    A size set to 0 means the corresponding key (KEY1, KEY2 or KEY3) is not
#    expected.
#
# It is expected that KEY1, KEY2 and KEY3 arrays are set correctly. Found key
# identifiers are stored in the right key array.
check_keys()
{
	n=$((n+1))
	echo_i "check keys are created for zone ${ZONE} ($n)"
	ret=0

	_key_algnum="${KEY1[$ALG_NUM]}"

	n=$((n+1))
	echo_i "check number of keys with algorithm ${_key_algnum} for zone ${ZONE} in dir ${DIR} ($n)"
	ret=0
	_numkeys=$(get_keyids $DIR $ZONE $_key_algnum | wc -l)
	test "$_numkeys" -eq $NUM_KEYS || log_error "bad number ($_numkeys) of key files for zone $ZONE (expected $NUM_KEYS)"
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))

	# Temporarily don't log errors because we are searching multiple files.
	_log=0

	# Clear key ids.
	KEY1[$ID]="0"
	KEY2[$ID]="0"
	KEY3[$ID]="0"

	# Check key files.
	_ids=$(get_keyids $DIR $ZONE "$_key_algnum")
	for _id in $_ids; do
		# There are three key files with the same algorithm.
		# Check them until a match is found.
		echo_i "check key $_id"

		if [ "0" == "${KEY1[$ID]}" ] && [ "${KEY1[$EXPECT]}" == "yes" ]; then
			ret=0
			check_key "KEY1" $_id
			test "$ret" -eq 0 && KEY1[$ID]=$KEY_ID && continue
		fi
		if [ "0" == "${KEY2[$ID]}" ] && [ "${KEY2[$EXPECT]}" == "yes" ]; then
			ret=0
			check_key "KEY2" $_id
			test "$ret" -eq 0 && KEY2[$ID]=$KEY_ID && continue
		fi
		if [ "0" == "${KEY3[$ID]}" ] && [ "${KEY3[$EXPECT]}" == "yes"  ]; then
			ret=0
			check_key "KEY3" $_id
			test "$ret" -eq 0 && KEY3[$ID]=$KEY_ID && continue
		fi

		# This may be an unused key.
		ret=0 && key_unused $_id
		test "$ret" -eq 0 && continue

		# If ret is still non-zero, non of the files matched.
		test "$ret" -eq 0 || echo_i "failed"
		status=$((status+ret))
	done

	# Turn error logs on again.
	_log=1

	ret=0
	if [ "${KEY1[$EXPECT]}" == "yes" ]; then
		test "0" == "${KEY1[$ID]}" && log_error "No KEY1 found for zone ${ZONE}"
	fi
	if [ "${KEY2[$EXPECT]}" == "yes" ]; then
		test "0" == "${KEY2[$ID]}" && log_error "No KEY2 found for zone ${ZONE}"
	fi
	if [ "${KEY3[$EXPECT]}" == "yes" ]; then
		test "0" == "${KEY3[$ID]}" && log_error "No KEY3 found for zone ${ZONE}"
	fi
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))
}

# Check if RRset of type $1 in file $2 is signed with the right keys.
# The right keys are the ones that expect a signature and matches the role $3.
check_signatures() {
	_qtype=$1
	_file=$2
	_role=$3

	if [ "${KEY1[$EXPECT_RRSIG]}" == "yes" ] && [ "${KEY1[$_role]}" == "yes" ]; then
		get_keys_which_signed $_qtype $_file | grep "^${KEY1[$ID]}$" > /dev/null || log_error "${_qtype} RRset not signed with key ${KEY1[$ID]}"
	elif [ "${KEY1[$EXPECT]}" == "yes" ]; then
		get_keys_which_signed $_qtype $_file | grep "^${KEY1[$ID]}$" > /dev/null && log_error "${_qtype} RRset signed unexpectedly with ${KEY1[$ID]}"
	fi

	if [ "${KEY2[$EXPECT_RRSIG]}" == "yes" ] && [ "${KEY2[$_role]}" == "yes" ]; then
		get_keys_which_signed $_qtype $_file | grep "^${KEY2[$ID]}$" > /dev/null || log_error "${_qtype} RRset not signed with ${KEY2[$ID]}"
	elif [ "${KEY2[$EXPECT]}" == "yes" ]; then
		get_keys_which_signed $_qtype $_file | grep "^${KEY2[$ID]}$" > /dev/null && log_error "${_qtype} RRset signed unexpectedly with ${KEY2[$ID]}"
	fi

	if [ "${KEY3[$EXPECT_RRSIG]}" == "yes" ] && [ "${KEY3[$_role]}" == "yes" ]; then
		get_keys_which_signed $_qtype $_file | grep "^${KEY3[$ID]}$" > /dev/null || log_error "${_qtype} RRset not signed with ${KEY3[$ID]}"
	elif [ "${KEY3[$EXPECT]}" == "yes" ]; then
		get_keys_which_signed $_qtype $_file | grep "^${KEY3[$ID]}$" > /dev/null && log_error "${_qtype} RRset signed unexpectedly with ${KEY3[$ID]}"
	fi
}

# Test the apex of a configured zone. This checks that the SOA and DNSKEY
# RRsets are signed correctly and with the appropriate keys.
check_apex() {

	# Test DNSKEY query.
	_qtype="DNSKEY"
	n=$((n+1))
	echo_i "check ${_qtype} rrset is signed correctly for zone ${ZONE} ($n)"
	ret=0
	dig_with_opts $ZONE @10.53.0.3 $_qtype > dig.out.$DIR.test$n || log_error "dig ${ZONE} ${_qtype} failed"
	grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
	grep "${ZONE}\..*${DNSKEY_TTL}.*IN.*${_qtype}.*257.*.3.*${_key_algnum}" dig.out.$DIR.test$n > /dev/null || log_error "missing ${_qtype} record in response"
	lines=$(get_keys_which_signed $_qtype dig.out.$DIR.test$n | wc -l)
	check_signatures $_qtype dig.out.$DIR.test$n $KSK
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))

	# Test SOA query.
	_qtype="SOA"
	n=$((n+1))
	echo_i "check ${_qtype} rrset is signed correctly for zone ${ZONE} ($n)"
	ret=0
	dig_with_opts $ZONE @10.53.0.3 $_qtype > dig.out.$DIR.test$n || log_error "dig ${ZONE} ${_qtype} failed"
	grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
	grep "${ZONE}\..*${DEFAULT_TTL}.*IN.*${_qtype}.*mname1\..*\." dig.out.$DIR.test$n > /dev/null || log_error "missing ${_qtype} record in response"
	lines=$(get_keys_which_signed $_qtype dig.out.$DIR.test$n | wc -l)
	check_signatures $_qtype dig.out.$DIR.test$n $ZSK
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))
}

# Test an RRset below the apex and verify it is signed correctly.
check_subdomain() {
	_qtype="A"
	n=$((n+1))
	echo_i "check ${_qtype} a.${ZONE} rrset is signed correctly for zone ${ZONE} ($n)"
	ret=0
	dig_with_opts a.$ZONE @10.53.0.3 $_qtype > dig.out.$DIR.test$n || log_error "dig a.${ZONE} ${_qtype} failed"
	grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
	grep "a.${ZONE}\..*${DEFAULT_TTL}.*IN.*${_qtype}.*10\.0\.0\.1" dig.out.$DIR.test$n > /dev/null || log_error "missing a.${ZONE} ${_qtype} record in response"
	lines=$(get_keys_which_signed $_qtype dig.out.$DIR.test$n | wc -l)
	check_signatures $_qtype dig.out.$DIR.test$n $ZSK
	test "$ret" -eq 0 || echo_i "failed"
	status=$((status+ret))
}

check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: dnssec-keygen.kasp.
#
zone_properties "ns3" "dnssec-keygen.kasp" "rsasha1" "1234" "3"
# key_properties, key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: some-keys.kasp.
#
zone_properties "ns3" "some-keys.kasp" "rsasha1" "1234" "3"
# key_properties, key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: legacy-keys.kasp.
#
zone_properties "ns3" "legacy-keys.kasp" "rsasha1" "1234" "3"
# key_properties, key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: pregenerated.kasp.
#
# There are more pregenerated keys than needed, hence the number of keys is
# six, not three.
zone_properties "ns3" "pregenerated.kasp" "rsasha1" "1234" "6"
# key_properties, key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

# TODO: we might want to test:
# - configuring a zone with too many active keys (should trigger retire).
# - configuring a zone with keys not matching the policy.

#
# Zone: rsasha1-nsec3.kasp.
#
zone_properties "ns3" "rsasha1-nsec3.kasp" "rsasha1-nsec3" "1234" "3"
key_properties "KEY1" "ksk" "315360000" "7" "NSEC3RSASHA1" "2048" "yes"
key_properties "KEY2" "zsk" "157680000" "7" "NSEC3RSASHA1" "1024" "yes"
key_properties "KEY3" "zsk" "31536000" "7" "NSEC3RSASHA1" "2000" "yes"
# key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: rsasha256.kasp.
#
zone_properties "ns3" "rsasha256.kasp" "rsasha256" "1234" "3"
key_properties "KEY1" "ksk" "315360000" "8" "RSASHA256" "2048" "yes"
key_properties "KEY2" "zsk" "157680000" "8" "RSASHA256" "1024" "yes"
key_properties "KEY3" "zsk" "31536000" "8" "RSASHA256" "2000" "yes"
# key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: rsasha512.kasp.
#
zone_properties "ns3" "rsasha512.kasp" "rsasha512" "1234" "3"
key_properties "KEY1" "ksk" "315360000" "10" "RSASHA512" "2048" "yes"
key_properties "KEY2" "zsk" "157680000" "10" "RSASHA512" "1024" "yes"
key_properties "KEY3" "zsk" "31536000" "10" "RSASHA512" "2000" "yes"
# key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: ecdsa256.kasp.
#
zone_properties "ns3" "ecdsa256.kasp" "ecdsa256" "1234" "3"
key_properties "KEY1" "ksk" "315360000" "13" "ECDSAP256SHA256" "256" "yes"
key_properties "KEY2" "zsk" "157680000" "13" "ECDSAP256SHA256" "256" "yes"
key_properties "KEY3" "zsk" "31536000" "13" "ECDSAP256SHA256" "256" "yes"
# key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: ecdsa512.kasp.
#
zone_properties "ns3" "ecdsa384.kasp" "ecdsa384" "1234" "3"
key_properties "KEY1" "ksk" "315360000" "14" "ECDSAP384SHA384" "384" "yes"
key_properties "KEY2" "zsk" "157680000" "14" "ECDSAP384SHA384" "384" "yes"
key_properties "KEY3" "zsk" "31536000" "14" "ECDSAP384SHA384" "384" "yes"
# key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify

# TODO: ED25519 and ED448.

#
# Zone: expired-sigs.autosign.
#
zone_properties "ns3" "expired-sigs.autosign" "autosign" "300" "2"
# Both KSK and ZSK stay OMNIPRESENT.
key_properties "KEY1" "ksk" "63072000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "published" "active" "retired" "none" "none"
key_states "KEY1" "omnipresent" "omnipresent" "none" "omnipresent" "omnipresent"
key_properties "KEY2" "zsk" "31536000" "13" "ECDSAP256SHA256" "256" "yes"
key_states "KEY2" "omnipresent" "omnipresent" "omnipresent" "none" "none"
key_timings "KEY2" "published" "active" "retired" "none" "none"
# Expect only two keys.
key_clear "KEY3"

check_keys
check_apex
check_subdomain
dnssec_verify

# Verify all signatures have been refreshed.
check_rrsig_refresh() {
	# Apex.
	_qtypes="DNSKEY SOA NS NSEC"
	for _qtype in $_qtypes
	do
		n=$((n+1))
		echo_i "check ${_qtype} rrsig is refreshed correctly for zone ${ZONE} ($n)"
		ret=0
		dig_with_opts $ZONE @10.53.0.3 $_qtype > dig.out.$DIR.test$n || log_error "dig ${ZONE} ${_qtype} failed"
		grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
		grep "${ZONE}\..*IN.*RRSIG.*${_qtype}.*${ZONE}" dig.out.$DIR.test$n > rrsig.out.$ZONE.$_qtype || log_error "missing RRSIG (${_qtype}) record in response"
		# If this exact RRSIG is also in the zone file it is not refreshed.
		_rrsig=`cat rrsig.out.$ZONE.$_qtype`
		grep "${_rrsig}" "${DIR}/${ZONE}.db" > /dev/null && log_error "RRSIG (${_qtype}) not refreshed in zone ${ZONE}"
		test "$ret" -eq 0 || echo_i "failed"
		status=$((status+ret))
	done

	# Below apex.
	_labels="a b c ns3"
	for _label in $_labels;
	do
		_qtypes="A NSEC"
		for _qtype in $_qtypes
		do
			n=$((n+1))
			echo_i "check ${_label} ${_qtype} rrsig is refreshed correctly for zone ${ZONE} ($n)"
			ret=0
			dig_with_opts "${_label}.${ZONE}" @10.53.0.3 $_qtype > dig.out.$DIR.test$n || log_error "dig ${_label}.${ZONE} ${_qtype} failed"
			grep "status: NOERROR" dig.out.$DIR.test$n > /dev/null || log_error "mismatch status in DNS response"
			grep "${ZONE}\..*IN.*RRSIG.*${_qtype}.*${ZONE}" dig.out.$DIR.test$n > rrsig.out.$ZONE.$_qtype || log_error "missing RRSIG (${_qtype}) record in response"
			_rrsig=`cat rrsig.out.$ZONE.$_qtype`
			grep "${_rrsig}" "${DIR}/${ZONE}.db" > /dev/null && log_error "RRSIG (${_qtype}) not refreshed in zone ${ZONE}"
			test "$ret" -eq 0 || echo_i "failed"
			status=$((status+ret))
		done
	done
}

check_rrsig_refresh

#
# Zone: unfresh-sigs.autosign.
#
zone_properties "ns3" "unfresh-sigs.autosign" "autosign" "300" "2"
# key_properties, key_timings and key_states same as above.
check_keys
check_apex
check_subdomain
dnssec_verify
check_rrsig_refresh

#
# Zone: zsk-missing.autosign.
#
zone_properties "ns3" "zsk-missing.autosign" "autosign" "300" "2"
# KSK stays OMNIPRESENT.
key_properties "KEY1" "ksk" "63072000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "published" "active" "retired" "none" "none"
key_states "KEY1" "omnipresent" "omnipresent" "none" "omnipresent" "omnipresent"
# key_properties, key_timings and key_states same as above.
# TODO

#
# Zone: zsk-retired.autosign.
#
zone_properties "ns3" "zsk-retired.autosign" "autosign" "300" "3"
# KSK properties, timings and states same as above.
# The ZSK goal is set to HIDDEN but records stay OMNIPRESENT until the new ZSK
# is active.
key_properties "KEY2" "zsk" "31536000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY2" "published" "active" "retired" "none" "none"
key_states "KEY2" "hidden" "omnipresent" "omnipresent" "none" "none"
# A new ZSK should be introduced, so expect a key with goal OMNIPRESENT,
# the DNSKEY introduced (RUMOURED) and the signatures HIDDEN.
key_properties "KEY3" "zsk" "31536000" "13" "ECDSAP256SHA256" "256" "no"
key_timings "KEY3" "published" "active" "retired" "none" "none"
key_states "KEY3" "omnipresent" "rumoured" "hidden" "none" "none"

#
# Testing ZSK Pre-Publication rollover.
#

#
# Zone: step1.zsk-prepub.autosign.
#
zone_properties "ns3" "step1.zsk-prepub.autosign" "zsk-prepub" "3600" "2"
# Both KSK (KEY1) and ZSK (KEY2) start in OMNIPRESENT.
key_properties "KEY1" "ksk" "63072000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "published" "active" "retired" "none" "none"
key_states "KEY1" "omnipresent" "omnipresent" "none" "omnipresent" "omnipresent"
key_properties "KEY2" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "yes"
key_states "KEY2" "omnipresent" "omnipresent" "omnipresent" "none" "none"
key_timings "KEY2" "published" "active" "retired" "none" "none"
# Initially only two keys.
key_clear "KEY3"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step2.zsk-prepub.autosign.
#
zone_properties "ns3" "step2.zsk-prepub.autosign" "zsk-prepub" "3600" "3"
# KSK (KEY1) doesn't change.
# ZSK (KEY2) remains active, no change in properties/timings/states.
# New ZSK (KEY3) is prepublished.
key_properties "KEY3" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "no"
key_states "KEY3" "omnipresent" "rumoured" "hidden" "none" "none"
key_timings "KEY3" "published" "active" "retired" "none" "none"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step3.zsk-prepub.autosign.
#
zone_properties "ns3" "step3.zsk-prepub.autosign" "zsk-prepub" "3600" "3"
# KSK (KEY1) doesn't change.
# ZSK (KEY2) properties and timing metadata same as above.
# ZSK (KEY2) no longer is actively signing, RRSIG state in UNRETENTIVE.
# New ZSK (KEY3) is now actively signing, RRSIG state in RUMOURED.
key_properties "KEY2" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "no"
key_states "KEY2" "hidden" "omnipresent" "unretentive" "none" "none"

key_properties "KEY3" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "yes"
key_states "KEY3" "omnipresent" "omnipresent" "rumoured" "none" "none"
check_keys
check_apex
# Subdomain still has good signatures of ZSK (KEY2)
key_properties "KEY2" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "yes"
key_properties "KEY3" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "no"
check_subdomain
dnssec_verify

#
# Zone: step4.zsk-prepub.autosign.
#
zone_properties "ns3" "step4.zsk-prepub.autosign" "zsk-prepub" "3600" "3"
# KSK (KEY1) doesn't change.
# ZSK (KEY2) properties and timing metadata same as above.
# ZSK (KEY2) DNSKEY is no longer needed.
# ZSK (KEY3) is now actively signing, RRSIG state in RUMOURED.
key_properties "KEY2" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "no"
key_states "KEY2" "hidden" "unretentive" "hidden" "none" "none"
key_properties "KEY3" "zsk" "2592000" "13" "ECDSAP256SHA256" "256" "yes"
key_states "KEY3" "omnipresent" "omnipresent" "omnipresent" "none" "none"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step5.zsk-prepub.autosign.
#
zone_properties "ns3" "step5.zsk-prepub.autosign" "zsk-prepub" "3600" "3"
# KSK (KEY1) doesn't change.
# ZSK (KEY2) properties and timing metadata same as above.
# ZSK (KEY3) DNSKEY is now completely HIDDEN and removed.
key_timings "KEY2" "published" "active" "retired" "none" "removed"
key_states "KEY2" "hidden" "hidden" "hidden" "none" "none"
# ZSK (KEY3) remains actively signing, staying in OMNIPRESENT.
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Testing KSK Double-KSK rollover.
#

#
# Zone: step1.ksk-doubleksk.autosign.
#
zone_properties "ns3" "step1.ksk-doubleksk.autosign" "ksk-doubleksk" "7200" "2"
# Both KSK (KEY1) and ZSK (KEY2) start in OMNIPRESENT.
key_properties "KEY1" "ksk" "5184000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY1" "published" "active" "retired" "none" "none"
key_states "KEY1" "omnipresent" "omnipresent" "none" "omnipresent" "omnipresent"
key_properties "KEY2" "zsk" "31536000" "13" "ECDSAP256SHA256" "256" "yes"
key_timings "KEY2" "published" "active" "retired" "none" "none"
key_states "KEY2" "omnipresent" "omnipresent" "omnipresent" "none" "none"
# Initially only two keys.
key_clear "KEY3"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step2.ksk-doubleksk.autosign.
#
zone_properties "ns3" "step2.ksk-doubleksk.autosign" "ksk-doubleksk" "7200" "3"
# ZSK (KEY2) doesn't change.
# KSK (KEY1) remains active, no change in properties/timings/states.
# New KSK (KEY3) is prepublished (and signs DNSKEY RRset).
key_properties "KEY3" "ksk" "5184000" "13" "ECDSAP256SHA256" "256" "yes"
key_states "KEY3" "omnipresent" "rumoured" "none" "rumoured" "hidden"
key_timings "KEY3" "published" "active" "retired" "none" "none"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step3.ksk-doubleksk.autosign.
#
zone_properties "ns3" "step3.ksk-doubleksk.autosign" "ksk-doubleksk" "7200" "3"
# ZSK (KEY2) doesn't change.
# KSK (KEY1) DS will be removed, so it is UNRETENTIVE.
key_states "KEY1" "hidden" "omnipresent" "none" "omnipresent" "unretentive"
# New KSK (KEY3) has its DS submitted.
key_states "KEY3" "omnipresent" "omnipresent" "none" "omnipresent" "rumoured"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step4.ksk-doubleksk.autosign.
#
zone_properties "ns3" "step4.ksk-doubleksk.autosign" "ksk-doubleksk" "7200" "3"
# ZSK (KEY2) doesn't change.
# KSK (KEY1) DNSKEY can be removed.
key_properties "KEY1" "ksk" "5184000" "13" "ECDSAP256SHA256" "256" "no"
key_states "KEY1" "hidden" "unretentive" "none" "unretentive" "hidden"
# New KSK (KEY3) DS is now OMNIPRESENT.
key_states "KEY3" "omnipresent" "omnipresent" "none" "omnipresent" "omnipresent"
check_keys
check_apex
check_subdomain
dnssec_verify

#
# Zone: step5.ksk-doubleksk.autosign.
#
zone_properties "ns3" "step5.ksk-doubleksk.autosign" "ksk-doubleksk" "7200" "3"
# ZSK (KEY2) doesn't change.
# KSK (KEY1) DNSKEY is now HIDDEN.
key_states "KEY1" "hidden" "hidden" "none" "hidden" "hidden"
# New KSK (KEY3) stays OMNIPRESENT.
check_keys
check_apex
check_subdomain
dnssec_verify

echo_i "exit status: $status"
[ $status -eq 0 ] || exit 1
