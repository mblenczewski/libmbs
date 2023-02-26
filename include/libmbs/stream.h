/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIBMBS_STREAM_H
#define LIBMBS_STREAM_H

#include "libmbs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct mbs_stream {
	u8 *ptr;
	u64 cur, len;
};

inline bool
mbs_stream_eof(struct mbs_stream *self) {
	assert(self);

	return self->len == self->cur;
}

inline u8 *
mbs_stream_headptr(struct mbs_stream *self) {
	assert(self);

	return self->ptr + self->cur;
}

inline bool
mbs_stream_skip(struct mbs_stream *self, u64 len) {
	assert(self);

	if (self->len - self->cur < len)
		return false;

	self->cur += len;

	return true;
}

inline bool
mbs_stream_peek(struct mbs_stream *self, u64 off, void *buf, u64 len) {
	assert(self);
	assert(buf);

	if (self->len - off - self->cur < len)
		return false;

	memcpy(buf, self->ptr + self->cur + off, len);

	return true;
}

inline bool
mbs_stream_consume(struct mbs_stream *self, void *buf, u64 len) {
	assert(self);
	assert(buf);

	return mbs_stream_peek(self, 0, buf, len) && mbs_stream_skip(self, len);
}

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* LIBMBS_STREAM_H */
