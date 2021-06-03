# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

# Clean up after rrl tests.

rm -f dig.out* *mdig.out*
rm -f  */named.memstats */named.run */named.stats */log-* */session.key
rm -f ns3/bl*.db */*.jnl */*.core */*.pid
rm -f ns*/named.lock
rm -f ns*/named.conf
rm -f broken.out
rm -f ns*/managed-keys.bind*
