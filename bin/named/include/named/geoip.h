/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

extern dns_geoip_databases_t *named_g_geoip;

void
named_geoip_init(void);

void
named_geoip_load(char *dir);

void
named_geoip_unload(void);

void
named_geoip_shutdown(void);
