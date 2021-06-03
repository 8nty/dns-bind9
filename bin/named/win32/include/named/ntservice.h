/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NTSERVICE_H
#define NTSERVICE_H

#include <winsvc.h>

#define BIND_DISPLAY_NAME "ISC BIND"
#define BIND_SERVICE_NAME "named"

void
     ntservice_init(void);
void UpdateSCM(DWORD);
void
ServiceControl(DWORD dwCtrlCode);
void
ntservice_shutdown(void);
BOOL
ntservice_isservice(void);
#endif /* ifndef NTSERVICE_H */
