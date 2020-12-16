/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

#include <stdlib.h>
#include <string.h>

#include <isc/app.h>
#include <isc/base64.h>
#include <isc/hash.h>
#include <isc/log.h>
#include <isc/managers.h>
#include <isc/mem.h>
#include <isc/nonce.h>
#include <isc/print.h>
#include <isc/random.h>
#include <isc/sockaddr.h>
#include <isc/socket.h>
#include <isc/task.h>
#include <isc/timer.h>
#include <isc/util.h>

#include <pk11/site.h>

#include <dns/dispatch.h>
#include <dns/fixedname.h>
#include <dns/keyvalues.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/request.h>
#include <dns/result.h>
#include <dns/tkey.h>
#include <dns/tsig.h>
#include <dns/view.h>

#include <dst/result.h>

#define CHECK(str, x)                                        \
	{                                                    \
		if ((x) != ISC_R_SUCCESS) {                  \
			fprintf(stderr, "I:%s: %s\n", (str), \
				isc_result_totext(x));       \
			exit(-1);                            \
		}                                            \
	}

#define RUNCHECK(x) RUNTIME_CHECK((x) == ISC_R_SUCCESS)

#define TIMEOUT 30

static char *ip_address = NULL;
static int port = 0;

static dst_key_t *ourkey;
static isc_mem_t *mctx;
static dns_tsigkey_t *tsigkey, *initialkey;
static dns_tsig_keyring_t *ring;
static unsigned char noncedata[16];
static isc_buffer_t nonce;
static dns_requestmgr_t *requestmgr;
static const char *ownername_str = ".";

static void
recvquery(isc_task_t *task, isc_event_t *event) {
	dns_requestevent_t *reqev = (dns_requestevent_t *)event;
	isc_result_t result;
	dns_message_t *query, *response;
	char keyname[256];
	isc_buffer_t keynamebuf;
	int type;

	UNUSED(task);

	REQUIRE(reqev != NULL);

	if (reqev->result != ISC_R_SUCCESS) {
		fprintf(stderr, "I:request event result: %s\n",
			isc_result_totext(reqev->result));
		exit(-1);
	}

	query = reqev->ev_arg;

	response = NULL;
	dns_message_create(mctx, DNS_MESSAGE_INTENTPARSE, &response);

	result = dns_request_getresponse(reqev->request, response,
					 DNS_MESSAGEPARSE_PRESERVEORDER);
	CHECK("dns_request_getresponse", result);

	if (response->rcode != dns_rcode_noerror) {
		result = ISC_RESULTCLASS_DNSRCODE + response->rcode;
		fprintf(stderr, "I:response rcode: %s\n",
			isc_result_totext(result));
		exit(-1);
	}

	result = dns_tkey_processdhresponse(query, response, ourkey, &nonce,
					    &tsigkey, ring);
	CHECK("dns_tkey_processdhresponse", result);

	/*
	 * Yes, this is a hack.
	 */
	isc_buffer_init(&keynamebuf, keyname, sizeof(keyname));
	result = dst_key_buildfilename(tsigkey->key, 0, "", &keynamebuf);
	CHECK("dst_key_buildfilename", result);
	printf("%.*s\n", (int)isc_buffer_usedlength(&keynamebuf),
	       (char *)isc_buffer_base(&keynamebuf));
	type = DST_TYPE_PRIVATE | DST_TYPE_PUBLIC | DST_TYPE_KEY;
	result = dst_key_tofile(tsigkey->key, type, "");
	CHECK("dst_key_tofile", result);

	dns_message_detach(&query);
	dns_message_detach(&response);
	dns_request_destroy(&reqev->request);
	isc_event_free(&event);
	isc_app_shutdown();
	return;
}

static void
sendquery(isc_task_t *task, isc_event_t *event) {
	struct in_addr inaddr;
	isc_sockaddr_t address;
	isc_region_t r;
	isc_result_t result;
	dns_fixedname_t keyname;
	dns_fixedname_t ownername;
	isc_buffer_t namestr, keybuf;
	unsigned char keydata[9];
	dns_message_t *query;
	dns_request_t *request;
	static char keystr[] = "0123456789ab";

	isc_event_free(&event);

	result = ISC_R_FAILURE;
	if (inet_pton(AF_INET, ip_address, &inaddr) != 1) {
		CHECK("inet_pton", result);
	}
	isc_sockaddr_fromin(&address, &inaddr, port);

	dns_fixedname_init(&keyname);
	isc_buffer_constinit(&namestr, "tkeytest.", 9);
	isc_buffer_add(&namestr, 9);
	result = dns_name_fromtext(dns_fixedname_name(&keyname), &namestr, NULL,
				   0, NULL);
	CHECK("dns_name_fromtext", result);

	dns_fixedname_init(&ownername);
	isc_buffer_constinit(&namestr, ownername_str, strlen(ownername_str));
	isc_buffer_add(&namestr, strlen(ownername_str));
	result = dns_name_fromtext(dns_fixedname_name(&ownername), &namestr,
				   NULL, 0, NULL);
	CHECK("dns_name_fromtext", result);

	isc_buffer_init(&keybuf, keydata, 9);
	result = isc_base64_decodestring(keystr, &keybuf);
	CHECK("isc_base64_decodestring", result);

	isc_buffer_usedregion(&keybuf, &r);

	initialkey = NULL;
	result = dns_tsigkey_create(
		dns_fixedname_name(&keyname), DNS_TSIG_HMACMD5_NAME,
		isc_buffer_base(&keybuf), isc_buffer_usedlength(&keybuf), false,
		NULL, 0, 0, mctx, ring, &initialkey);
	CHECK("dns_tsigkey_create", result);

	query = NULL;
	dns_message_create(mctx, DNS_MESSAGE_INTENTRENDER, &query);

	result = dns_tkey_builddhquery(query, ourkey,
				       dns_fixedname_name(&ownername),
				       DNS_TSIG_HMACMD5_NAME, &nonce, 3600);
	CHECK("dns_tkey_builddhquery", result);

	request = NULL;
	result = dns_request_create(requestmgr, query, &address,
				    DNS_REQUESTOPT_TCP, initialkey, TIMEOUT,
				    task, recvquery, query, &request);
	CHECK("dns_request_create", result);
}

int
main(int argc, char *argv[]) {
	char *ourkeyname = NULL;
	isc_nm_t *netmgr = NULL;
	isc_taskmgr_t *taskmgr = NULL;
	isc_timermgr_t *timermgr = NULL;
	isc_socketmgr_t *socketmgr = NULL;
	isc_socket_t *sock = NULL;
	unsigned int attrs;
	isc_sockaddr_t bind_any;
	dns_dispatchmgr_t *dispatchmgr = NULL;
	dns_dispatch_t *dispatchv4 = NULL;
	dns_view_t *view = NULL;
	dns_tkeyctx_t *tctx = NULL;
	isc_log_t *log = NULL;
	isc_logconfig_t *logconfig = NULL;
	isc_task_t *task = NULL;
	isc_result_t result;
	int type;

	RUNCHECK(isc_app_start());

	if (argc < 4) {
		fprintf(stderr, "I:no DH key provided\n");
		exit(-1);
	}
	ip_address = argv[1];
	port = atoi(argv[2]);
	ourkeyname = argv[3];

	if (argc >= 5) {
		ownername_str = argv[4];
	}

	dns_result_register();

	mctx = NULL;
	isc_mem_debugging = ISC_MEM_DEBUGRECORD;
	isc_mem_create(&mctx);

	log = NULL;
	logconfig = NULL;
	isc_log_create(mctx, &log, &logconfig);

	RUNCHECK(dst_lib_init(mctx, NULL));

	isc_managers_create(mctx, 1, 0, 0, &netmgr, &taskmgr, &timermgr,
			    &socketmgr);

	RUNCHECK(isc_task_create(taskmgr, 0, &task));
	RUNCHECK(dns_dispatchmgr_create(mctx, &dispatchmgr));

	isc_sockaddr_any(&bind_any);
	attrs = DNS_DISPATCHATTR_UDP | DNS_DISPATCHATTR_MAKEQUERY |
		DNS_DISPATCHATTR_IPV4;
	RUNCHECK(dns_dispatch_createudp(dispatchmgr, socketmgr, taskmgr,
					&bind_any, 4, 2, 3, 5, attrs,
					&dispatchv4));
	requestmgr = NULL;
	RUNCHECK(dns_requestmgr_create(mctx, timermgr, socketmgr, taskmgr,
				       dispatchmgr, dispatchv4, NULL,
				       &requestmgr));

	ring = NULL;
	RUNCHECK(dns_tsigkeyring_create(mctx, &ring));
	tctx = NULL;
	RUNCHECK(dns_tkeyctx_create(mctx, &tctx));

	view = NULL;
	RUNCHECK(dns_view_create(mctx, 0, "_test", &view));
	dns_view_setkeyring(view, ring);
	dns_tsigkeyring_detach(&ring);

	sock = NULL;
	RUNCHECK(isc_socket_create(socketmgr, PF_INET, isc_sockettype_udp,
				   &sock));

	RUNCHECK(isc_app_onrun(mctx, task, sendquery, NULL));

	ourkey = NULL;
	type = DST_TYPE_PUBLIC | DST_TYPE_PRIVATE | DST_TYPE_KEY;
	result = dst_key_fromnamedfile(ourkeyname, NULL, type, mctx, &ourkey);
	CHECK("dst_key_fromnamedfile", result);

	isc_buffer_init(&nonce, noncedata, sizeof(noncedata));
	isc_nonce_buf(noncedata, sizeof(noncedata));
	isc_buffer_add(&nonce, sizeof(noncedata));

	(void)isc_app_run();

	dns_requestmgr_shutdown(requestmgr);
	dns_requestmgr_detach(&requestmgr);
	dns_dispatch_detach(&dispatchv4);
	dns_dispatchmgr_destroy(&dispatchmgr);
	isc_task_shutdown(task);
	isc_task_detach(&task);
	isc_socket_detach(&sock);
	isc_managers_destroy(&netmgr, &taskmgr, &timermgr, &socketmgr);

	dst_key_free(&ourkey);
	dns_tsigkey_detach(&initialkey);
	dns_tsigkey_detach(&tsigkey);

	dns_tkeyctx_destroy(&tctx);

	dns_view_detach(&view);

	isc_log_destroy(&log);

	dst_lib_destroy();

	isc_mem_destroy(&mctx);

	isc_app_finish();

	return (0);
}
