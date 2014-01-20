

#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum rb_color {
	RB_COLOR_RED,
	RB_COLOR_BLACK
};

struct rb_node {
	struct rb_node *p, *l, *r;
	enum rb_color clr;
};

struct rb_root {
	struct rb_node *root;
	struct rb_tmpl *tmpl;
};

struct rb_tmpl {
	struct rb_node *(*alloc_node)(va_list);
	void (*free_node)(struct rb_node *);
	int (*ins_preprocess)(struct rb_root*, struct rb_node*);
	struct rb_node *(*del_preprocess)(struct rb_root*, va_list);
	int (*order)(struct rb_node*, struct rb_node*);
};

/**
 * @n: the rb_node object
 * @s: the target structure
 * @e: the name of the rb_node field in the target structure
 */
#define rb_entry(n, s, e) \
		(s*)((char*)n - (unsigned long)&((s*)(0)->e))

static inline void rb_link_node(struct rb_node *n, struct rb_node *parent, struct rb_node **link)
{
	n->p = parent;
	n->l = n->r = NULL;
	*link = n;
}

void rb_erase(struct rb_node *node, struct rb_root *root);
void rb_balance(struct rb_node *node, struct rb_root *root);

#endif // _RBTREE_H_