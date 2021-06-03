/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#if HAVE_CMOCKA

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define UNIT_TESTING
#include <cmocka.h>

#include <isc/result.h>
#include <isc/util.h>

#include <isccc/result.h>

/*
 * Check tables are populated.
 */
static void
tables(void **state) {
	const char *str;
	isc_result_t result;

	UNUSED(state);

	isccc_result_register();

	for (result = ISC_RESULTCLASS_ISCCC;
	     result < (ISC_RESULTCLASS_ISCCC + ISCCC_R_NRESULTS); result++)
	{
		str = isc_result_toid(result);
		assert_non_null(str);
		assert_string_not_equal(str, "(result code text not "
					     "available)");

		str = isc_result_totext(result);
		assert_non_null(str);
		assert_string_not_equal(str, "(result code text not "
					     "available)");
	}

	str = isc_result_toid(result);
	assert_non_null(str);
	assert_string_equal(str, "(result code text not available)");

	str = isc_result_totext(result);
	assert_non_null(str);
	assert_string_equal(str, "(result code text not available)");
}

int
main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(tables),
	};

	return (cmocka_run_group_tests(tests, NULL, NULL));
}

#else /* HAVE_CMOCKA */

#include <stdio.h>

int
main(void) {
	printf("1..0 # Skipped: cmocka not available\n");
	return (SKIPPED_TEST_EXIT_CODE);
}

#endif /* if HAVE_CMOCKA */
