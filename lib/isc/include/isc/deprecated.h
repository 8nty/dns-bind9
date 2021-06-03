/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_DEPRECATED_H
#define ISC_DEPRECATED_H

#if (__GNUC__ + 0) > 3
#define ISC_DEPRECATED __attribute__((deprecated))
#else		       /* if (__GNUC__ + 0) > 3 */
#define ISC_DEPRECATED /* none */
#endif		       /* __GNUC__ > 3*/

#endif /* ifndef ISC_DEPRECATED_H */
