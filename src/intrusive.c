/*
 * Copyright (c) 2023, Mikolaj Lenczewski <mblenczewski@gmail.com>
 *
 * SPDX-License-Identifier: MIT-0
 */

#include "libmbs/intrusive.h"

extern inline void
mbs_intrusive_list_node_link(struct mbs_intrusive_list_node *self,
			     struct mbs_intrusive_list_node *prev,
			     struct mbs_intrusive_list_node *next);

extern inline void
mbs_intrusive_list_node_snip(struct mbs_intrusive_list_node *self);

extern inline void
mbs_intrusive_list_node_restore(struct mbs_intrusive_list_node *self);

extern inline void
mbs_intrusive_list_push_head(struct mbs_intrusive_list *self,
			     struct mbs_intrusive_list_node *node);
