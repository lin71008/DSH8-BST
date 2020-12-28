#include <stdio.h>
#include <stdlib.h>

#include "product_list.h"

#include "bst.h"
#include "product.h"

static int highest_price;

static int value_delete(void*);
static int product_tree_node_delete(node**);
static int temp_tree_node_delete(node**);
static void* key_gen(pdata*);
static int key_cmp(const void*, const void*);
static int value_filter(const void*);

node* product_tree_create(void)
{
	return NULL;
}

int product_tree_delete(node **dest)
{
	return tree_delete(dest, product_tree_node_delete);
}

int temp_tree_delete(node **dest)
{
	return tree_delete(dest, temp_tree_node_delete);
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

int product_tree_display (FILE *fp, const char *format, const node *source)
{
	if (source == NULL || format == NULL || fp == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		product_tree_display(fp, format, source->left);
		pdata_display(fp, format, product_tree_node_get_value(source));
		product_tree_display(fp, format, source->right);
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

node* product_tree_get_highest_price_node(node **dest)
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The node is empty
	{
		return NULL;
	}
	highest_price = 0;
	node *temp = NULL, *temp2 = NULL;
	if (tree_get_node_by_value_filter(&temp, dest, value_filter) <= 0)  // Setup highest_price
	{
		return NULL;  // Noting in tree that price > 0
	}
	if (tree_get_node_by_value_filter(&temp2, &temp, value_filter) <= 0) // Get node that price equal to highest_price
	{
		tree_delete(&temp, temp_tree_node_delete);
		return NULL;  // Unknown Error
	}
	else
	{
		tree_delete(&temp, temp_tree_node_delete);
		return temp2;
	}
}

static int product_tree_node_delete(node **dest)
{
	return node_delete(dest, NULL, value_delete);
}

static int temp_tree_node_delete(node **dest)
{
	return node_delete(dest, NULL, NULL);
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
	if (k1 == NULL || k2 == NULL)  // Undefined behavior
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

static int value_filter(const void *v)
{
	if (v == NULL)  // Undefined behavior
	{
		return 0;
	}
	int temp = pdata_get_price((const pdata*) v);
	if (temp >= highest_price)
	{
		highest_price = temp;
		return 1;
	}
	else
	{
		return 0;
	}
}
