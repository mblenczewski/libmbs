/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIBMBS_STRVIEW_H
#define LIBMBS_STRVIEW_H

#include "libmbs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct mbs_strview {
	char *ptr;
	u64 len;
};

inline bool
mbs_strview_equal(struct mbs_strview a, struct mbs_strview b) {
	return a.len == b.len && strncmp(a.ptr, b.ptr, a.len) == 0;
}

#define MBS_CONST_CSTR_SV(ccstr) \
((struct mbs_strview){ .ptr = ccstr, .len = sizeof(ccstr) - 1, })

#define MBS_CSTR_SV(cstr) \
((struct mbs_strview){ .ptr = cstr, .len = strlen(cstr), })

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* LIBMBS_STRVIEW_H */
