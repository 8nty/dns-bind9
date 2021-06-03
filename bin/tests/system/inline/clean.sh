# SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0

rm -rf ./*/*.jbk \
   ./*/*.nzd ./*/*.nzd-lock ./*/*.nzf \
   ./*/named.conf ./*/named.memstats ./*/named.run* ./*/named.lock \
   ./*/trusted.conf \
   ./K* ./*/K* \
   ./checkecdsa \
   ./freeze.test* thaw.test* \
   ./import.key \
   ././ns*/managed-keys.bind* ./ns*/*.mkeys* \
   ./*/dsset-* ./*/nzf-* \
   ./*/*.db ./*/*.db.signed ./*/*.db.jnl ./*/*.db.signed.jnl \
   ./*.out ./*.out* ./*/*.out ./*/*.out* \
   ./*/*.bk ./*/*.bk.jnl ./*/*.bk.signed ./*/*.bk.signed.jnl \
   ns3/a-file ns3/removedkeys
