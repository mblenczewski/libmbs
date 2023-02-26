/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#ifndef LIBMBS_INTRUSIVE_H
#define LIBMBS_INTRUSIVE_H

#include "libmbs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef u64 mbs_intrusive_relptr;

struct mbs_intrusive_list_node {
	mbs_intrusive_relptr prev, next;
};

#define INTRUSIVE_LIST_NODE_DATA_PTR(type, node_member_name, node_absptr) \
((type *)((u8 *)(node_absptr) - offsetof(type, node_member_name)))

inline void
mbs_intrusive_list_node_link(struct mbs_intrusive_list_node *self,
			     struct mbs_intrusive_list_node *prev,
			     struct mbs_intrusive_list_node *next) {
	assert(self);
	assert(prev);
	assert(next);

	prev->next = RELPTR_ABS2REL(mbs_intrusive_relptr, prev, self);
	self->prev = RELPTR_ABS2REL(mbs_intrusive_relptr, self, prev);
	self->next = RELPTR_ABS2REL(mbs_intrusive_relptr, self, next);
	next->prev = RELPTR_ABS2REL(mbs_intrusive_relptr, next, self);
}

inline void
mbs_intrusive_list_node_snip(struct mbs_intrusive_list_node *self) {
	assert(self);

	struct mbs_intrusive_list_node *prev, *next;
	prev = RELPTR_REL2ABS(struct mbs_intrusive_list_node *, mbs_intrusive_relptr, self, self->prev);
	next = RELPTR_REL2ABS(struct mbs_intrusive_list_node *, mbs_intrusive_relptr, self, self->next);

	prev->next = RELPTR_ABS2REL(mbs_intrusive_relptr, prev, next);
	next->prev = RELPTR_ABS2REL(mbs_intrusive_relptr, next, prev);
}

inline void
mbs_intrusive_list_node_restore(struct mbs_intrusive_list_node *self) {
	assert(self);

	struct mbs_intrusive_list_node *prev, *next;
	prev = RELPTR_REL2ABS(struct mbs_intrusive_list_node *, mbs_intrusive_relptr, self, self->prev);
	next = RELPTR_REL2ABS(struct mbs_intrusive_list_node *, mbs_intrusive_relptr, self, self->next);

	mbs_intrusive_list_node_link(self, prev, next);
}

struct mbs_intrusive_list {
	struct mbs_intrusive_list_node root;
};

inline void
mbs_intrusive_list_push_head(struct mbs_intrusive_list *self,
			     struct mbs_intrusive_list_node *node) {
	assert(self);
	assert(node);

	struct mbs_intrusive_list_node *prev, *next;
	prev = &self->root;
	next = RELPTR_REL2ABS(struct mbs_intrusive_list_node *, mbs_intrusive_relptr, &self->root, self->root.next);

	mbs_intrusive_list_node_link(node, prev, next);
}

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* LIBMBS_INTRUSIVE_H */
