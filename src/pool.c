/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "libmbs/pool.h"

extern inline bool
mbs_pool_init(struct mbs_pool *self, u64 alignment, u64 capacity);

extern inline void
mbs_pool_free(struct mbs_pool *self);

extern inline void
mbs_pool_reset(struct mbs_pool *self);

extern inline bool
mbs_pool_prealloc(struct mbs_pool *self, u64 alignment, u64 size);

extern inline void *
mbs_pool_alloc(struct mbs_pool *self, u64 alignment, u64 size);
