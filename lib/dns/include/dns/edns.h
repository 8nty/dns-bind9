/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_EDNS_H
#define DNS_EDNS_H 1

/*%
 * The maximum version on EDNS supported by this build.
 */
#define DNS_EDNS_VERSION 0
#ifdef DRAFT_ANDREWS_EDNS1
#undef DNS_EDNS_VERSION
/*
 * Warning: this currently disables sending COOKIE requests in resolver.c
 */
#define DNS_EDNS_VERSION 1 /* draft-andrews-edns1 */
#endif			   /* ifdef DRAFT_ANDREWS_EDNS1 */

#endif /* ifndef DNS_EDNS_H */
