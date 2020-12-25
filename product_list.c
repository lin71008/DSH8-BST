#include <stdio.h>
#include <stdlib.h>

#include "product_list.h"

#include "bst.h"
#include "product.h"

static int value_delete(void*);
static int product_tree_node_delete(node**);
static void* key_gen(pdata*);
static int key_cmp(const void*, const void*);

node* product_tree_create(void)
{
	return NULL;
}

int product_tree_delete(node **dest)
{
	return tree_delete(dest, product_tree_node_delete);
}

int product_tree_node_get_key(const node *source)
{
	void* temp = node_get_key(source);
	if (temp == NULL)
	{
		return -1;
	}
	else
	{
		return *((int*) temp);
	}
}

pdata* product_tree_node_get_value(const node *source)
{
	void* temp = node_get_value(source);
	if (temp == NULL)
	{
		return NULL;
	}
	else
	{
		return ((pdata*) temp);
	}
}

int product_tree_display (const node *source, FILE *fp)
{
	if (source == NULL || fp == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		product_tree_display(source->left, fp);
		pdata_display(product_tree_node_get_value(source), fp);
		product_tree_display(source->right, fp);
		return 0;
	}
}

int product_tree_add_pdata(node **dest, pdata *data)
{
	if (data == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		return tree_add_node(dest, key_gen(data), data, key_cmp);
	}
}

int product_tree_remove_node_by_key(node **dest, const int key)
{
	return tree_remove_node_by_key(dest, &key, product_tree_node_delete, key_cmp);
}

pdata* product_tree_get_pdata_by_key(node **dest, const int key)
{
	node **temp = tree_get_node_by_key(dest, &key, key_cmp);
	if (temp == NULL)
	{
		return NULL;
	}
	else
	{
		return product_tree_node_get_value((*temp));
	}
}

node** product_tree_get_previous_node_by_key(node **dest, const int key)
{
	return tree_get_previous_node_by_key(dest, &key, key_cmp);
}

node** product_tree_get_next_node_by_key(node **dest, const int key)
{
	return tree_get_next_node_by_key(dest, &key, key_cmp);
}

node** product_tree_get_highest_price_node(node **dest)
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The node is empty
	{
		return NULL;
	}
	return NULL;
}

static int product_tree_node_delete(node **dest)
{
	return node_delete(dest, NULL, value_delete);
}

static int value_delete(void *val)
{
	return pdata_delete((pdata**) val);
}

static void* key_gen(pdata *dest)
{
	return pdata_get_key(dest);
}

static int key_cmp(const void *k1, const void *k2)
{
	if (k1 == NULL || k2 == NULL)
	{
		return 0;
	}
	else if (*((int*) k1) > *((int*) k2))
	{
		return -1;
	}
	else if (*((int*) k1) < *((int*) k2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
