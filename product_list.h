#ifndef __PRODUCT_LIST_H__
#define __PRODUCT_LIST_H__

typedef struct node node;
typedef struct product_type pdata;

// product_tree: __init__, __del__
extern node* product_tree_create(void);
extern int product_tree_delete(node**);

// product_tree: node: get
extern int product_tree_node_get_key(const node*);
extern pdata* product_tree_node_get_value(const node*);

// product_tree: __str__
extern const char* product_tree_toString(const node**, const char* (*)(const pdata*));

// product_tree: display
extern int product_tree_display(FILE*, const char*,const node*);

// product_tree: add, remove
extern int product_tree_add_pdata(node**, pdata*);
extern int product_tree_remove_node_by_key(node**, const int);

// product_tree: search
extern pdata* product_tree_get_pdata_by_key(node**, const int);

// product_tree: previous, next
extern node** product_tree_get_previous_node_by_key(node**, const int);
extern node** product_tree_get_next_node_by_key(node**, const int);

// product_tree: highest_price_node
extern node** product_tree_get_highest_price_node(node**);

#endif
