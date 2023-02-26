/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIBMBS_POOL_H
#define LIBMBS_POOL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct mbs_pool {
	u8 *ptr;
	u64 cap, len;
};

inline bool
mbs_pool_init(struct mbs_pool *self, u64 alignment, u64 capacity) {
	assert(self);
	assert(alignment);
	assert(capacity % alignment == 0);

	u8 *ptr = aligned_alloc(alignment, capacity);
	if (!ptr) return false;

	self->ptr = ptr;
	self->cap = capacity;
	self->len = 0;

	return true;
}

inline void
mbs_pool_free(struct mbs_pool *self) {
	assert(self);

	free(self->ptr);
}

inline void
mbs_pool_reset(struct mbs_pool *self) {
	assert(self);

	self->len = 0;
}

inline bool
mbs_pool_prealloc(struct mbs_pool *self, u64 alignment, u64 size) {
	assert(self);
	assert(alignment);
	assert(size % alignment == 0);

	return self->len + size <= self->cap;
}

inline void *
mbs_pool_alloc(struct mbs_pool *self, u64 alignment, u64 size) {
	assert(self);
	assert(alignment);
	assert(alignment == 1 || alignment % 2 == 0);

	u64 alignment_mask = alignment - 1;
	u64 aligned_len = (self->len + alignment_mask) & ~alignment_mask;

	if (!mbs_pool_prealloc(self, alignment, (aligned_len - self->len) + size))
		return NULL;

	void *ptr = self->ptr + aligned_len;
	self->len = aligned_len + size;

	return ptr;
}

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* LIBMBS_POOL_H */
