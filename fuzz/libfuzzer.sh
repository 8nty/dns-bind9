#!/bin/sh -ex

# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

#
exec "${2}" "${1}/$(basename "${2}").in" -max_total_time=5 -print_pcs=1 -print_final_stats=1 -print_corpus_stats=1 -print_coverage=1
