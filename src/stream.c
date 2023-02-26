/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "libmbs/stream.h"

extern inline bool
mbs_stream_eof(struct mbs_stream *self);

extern inline u8 *
mbs_stream_headptr(struct mbs_stream *self);

extern inline bool
mbs_stream_skip(struct mbs_stream *self, u64 len);

extern inline bool
mbs_stream_peek(struct mbs_stream *self, u64 off, void *buf, u64 len);

extern inline bool
mbs_stream_consume(struct mbs_stream *self, void *buf, u64 len);
