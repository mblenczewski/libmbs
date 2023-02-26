/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIBMBS_TEST_H
#define LIBMBS_TEST_H

#include "libmbs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TEST_PASS() return 1;
#define TEST_FAIL() return 0;

#define TESTS_BEGIN() s32 __test_suite_result = 0;
#define TESTS_END() return __test_suite_result;

#define TEST_RUN(name) \
do { \
	fprintf(stderr, "%s:%s:\n", __FILE__, #name); \
	if (name()) { \
		fprintf(stderr, "%s:%s: OK\n", __FILE__, #name); \
	} else { \
		fprintf(stderr, "%s:%s: FAILED\n", __FILE__, #name); \
		__test_suite_result = 1; \
	} \
} while (0);

#define _TEST_ASSERT_IMPL(cond, msg) \
fprintf(stderr, "[%s:%d] %s: %s\n", __func__, __LINE__, #cond, msg)

#define TEST_ASSERT(cond, msg) \
if (!(cond)) { _TEST_ASSERT_IMPL(cond, msg); TEST_FAIL() }

#define TEST_EXPECT(cond, msg) \
if (!(cond)) { _TEST_ASSERT_IMPL(cond, msg); }

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* LIBMBS_TEST_H */
