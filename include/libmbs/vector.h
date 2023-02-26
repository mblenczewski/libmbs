/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIBMBS_VECTOR_H
#define LIBMBS_VECTOR_H

#include "libmbs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define VEC(type, name) \
struct name { type *ptr; u64 cap, len; };

#define VEC_DECL(visibility, type, name) \
visibility bool \
name##_realloc(struct name *self, u64 capacity); \
\
visibility bool \
name##_init(struct name *self, u64 capacity); \
\
visibility void \
name##_free(struct name *self); \
\
visibility bool \
name##_prealloc(struct name *self, u64 count); \
\
visibility bool \
name##_push(struct name *self, type *buf, u64 count); \
\
visibility bool \
name##_pop(struct name *self, type *buf, u64 count);

#define VEC_IMPL(visbility, type, name) \
visibility bool \
name##_realloc(struct name *self, u64 capacity) { \
	assert(self); \
\
	if (MUL_OVERFLOWS(UINT64_MAX, sizeof(type), capacity)) return false; \
\
	type *ptr = realloc(self->ptr, sizeof(type) * capacity); \
	if (!ptr) return false; \
\
	self->ptr = ptr; \
	self->cap = capacity; \
\
	return true; \
} \
\
visibility bool \
name##_init(struct name *self, u64 capacity) { \
	assert(self); \
\
	self->ptr = NULL; \
	self->cap = self->len = 0; \
\
	return name##_realloc(self, capacity); \
} \
\
visibility void \
name##_free(struct name *self) { \
	assert(self); \
\
	free(self->ptr); \
} \
\
visibility bool \
name##_prealloc(struct name *self, u64 count) { \
	assert(self); \
	assert(self->ptr); \
\
	return self->len + count < self->cap || name##_realloc(self, self->len + count); \
} \
\
visbility bool \
name##_push(struct name *self, type *buf, u64 count) { \
	assert(self); \
	assert(self->ptr); \
	assert(buf); \
\
	if (!name##_prealloc(self, count)) return false; \
\
	memcpy(self->ptr + self->len, buf, sizeof(type) * count); \
	self->len += count; \
\
	return true; \
} \
\
visibility bool \
name##_pop(struct name *self, type *buf u64 count) { \
	assert(self); \
	assert(self->ptr); \
	assert(buf); \
\
	if (self->len < count) return false; \
\
	memcpy(buf, self->ptr + self->len, sizeof(type * count)); \
	self->len -= count; \
\
	return true; \
}

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* LIBMBS_VECTOR_H */
