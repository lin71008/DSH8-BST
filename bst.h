#ifndef __BST__H__
#define __BST__H__

typedef struct node
{
	void *key, *value;
	struct node *left, *right;
} node;

// node: __init__, __del__
extern node* node_create(void*, void*);
extern int node_delete(node**, int (*)(void*), int (*)(void*));

// node: get
extern void* node_get_key(const node*);
extern void* node_get_value(const node*);

// tree: __init__, __del__
extern node* tree_create(void);
extern int tree_delete(node**, int (*)(node**));

// tree: add, remove
extern int tree_add_node(node**, void*, void*, int (*)(const void*, const void*));
extern int tree_remove_root_node(node**, int (*)(node**), int (*)(const void*, const void*));
extern int tree_remove_node_by_key(node**, const void*, int (*)(node**), int (*)(const void*, const void*));

// tree: leftmost, rightmost
extern node** tree_get_leftmost_node(node**);
extern node** tree_get_rightmost_node(node**);

// tree: search
extern node** tree_get_node_by_key(node**, const void*, int (*)(const void*, const void*));

// tree: Filted by value filter
extern int tree_get_node_by_value_filter(node**, node**, int (*)(const void*));

// tree: previous, next
extern node** tree_get_previous_node_by_key(node**, const void*, int (*)(const void*, const void*));
extern node** tree_get_next_node_by_key(node**, const void*, int (*)(const void*, const void*));

#endif

// if \([a-zA-Z\+\-\+\\\=_\(\)\ !0-9\/]+\n[\t\ a-zA-Z\+\-\+\\\=_\(\)\ !0-9\/{\n;]+}[\n\t]+ret
