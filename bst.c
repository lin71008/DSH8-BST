#include <stdlib.h>

#include "bst.h"

node* create_node(void* key, void* val)
{
	node *ret = (node*) malloc(sizeof(node));
	if (ret == NULL)  // RuntimeError, can not allocate new node
	{
		return NULL;
	}
	ret->key = key;
	ret->value = val;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

int node_delete(node **dest, int (*key_delete)(void*), int (*value_delete)(void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	if ((*dest) == NULL)  // The node is empty
	{
		return 0;
	}
	if (key_delete != NULL)
	{
		key_delete(&((*dest)->key));
	}
	(*dest)->key = NULL;
	if (value_delete != NULL)
	{
		value_delete(&((*dest)->value));
	}
	(*dest)->value = NULL;
	free((*dest));
	(*dest) = NULL;
	return 0;
}

void* node_get_key(const node *source)
{
	if (source == NULL)  // Undefined behavior
	{
		return NULL;
	}
	else
	{
		return source->key;
	}
}

void* node_get_value(const node *source)
{
	if (source == NULL)  // Undefined behavior
	{
		return NULL;
	}
	else
	{
		return source->value;
	}
}

node* tree_create(void)
{
	return NULL;
}

int tree_delete(node **dest, int (*node_delete)(node**))
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return 0;
	}
	if (tree_delete(&((*dest)->left), node_delete) == 0 && tree_delete(&((*dest)->right), node_delete) == 0)
	{
		if (node_delete(dest) != 0)  // UnknownError
		{
			return -1;
		}
		(*dest) = NULL;
		return 0;
	}
	return -1;  // UnknownError
}

int tree_add_node(node **dest, void *key, void *val, int (*key_cmp)(const void*, const void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	if ((*dest) == NULL)
	{
		node *n = create_node(key, val);
		if (n == NULL)  // RuntimeError, can not allocate new node
		{
			return -1;
		}
		(*dest) = n;
		return 0;
	}
	else if (key_cmp((*dest)->key, key) == -1)
	{
		return tree_add_node(&((*dest)->left), key, val, key_cmp);
	}
	else if (key_cmp((*dest)->key, key) == 1)
	{
		return tree_add_node(&((*dest)->right), key, val, key_cmp);
	}
	else  // ValueError, the key is already in used
	{
		return 1;
	}
}

int tree_remove_root_node(node **dest, int (*node_delete)(node**), int (*key_cmp)(const void*, const void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return 1;
	}
	if ((*dest)->left != NULL)
	{
		node** temp = tree_get_rightmost_node(&((*dest)->left));
		node* new_dest = (*temp);
		new_dest->left = (*dest)->left;
		new_dest->right = (*dest)->right;
		if (node_delete(dest) != 0)  // UnknownError
		{
			new_dest->left = NULL;
			new_dest->right = NULL;
			return -1;
		}
		(*dest) = new_dest;
		(*temp) = NULL;
		return 0;
	}
	else
	{
		node *new_dest = (*dest)->right;
		if (node_delete(dest) != 0)  // UnknownError
		{
			return -1;
		}
		(*dest) = new_dest;
		return 0;
	}
}

int tree_remove_node_by_key(node **dest, const void *key, int (*node_delete)(node**), int (*key_cmp)(const void*, const void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return 1;
	}
	node **temp = tree_get_node_by_key(dest, key, key_cmp);
	if (temp == NULL)  // The key is unused
	{
		return 1;
	}
	else
	{
		return 	tree_remove_root_node(temp, node_delete, key_cmp);
	}
}

node** tree_get_leftmost_node(node **dest)
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return dest;
	}
	while ((*dest)->left != NULL)
	{
		dest = &((*dest)->left);
	}
	return dest;
}

node** tree_get_rightmost_node(node **dest)
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return dest;
	}
	while ((*dest)->right != NULL)
	{
		dest = &((*dest)->right);
	}
	return dest;
}

node** tree_get_node_by_key(node **dest, const void *key, int (*key_cmp)(const void*, const void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return NULL;
	}
	while ((*dest) != NULL)
	{
		if (key_cmp((*dest)->key, key) == -1)
		{
			dest = &((*dest)->left);
		}
		else if (key_cmp((*dest)->key, key) == 1)
		{
			dest = &((*dest)->right);
		}
		else
		{
			break;
		}
	}
	if ((*dest) == NULL)  // The key is unused
	{
		return NULL;
	}
	else
	{
		return dest;
	}
}

node** tree_get_previous_node_by_key(node **dest, const void *key, int (*key_cmp)(const void*, const void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return NULL;
	}
	node **temp = tree_get_node_by_key(dest, key, key_cmp);
	if (temp == NULL)  // The key is unused
	{
		return NULL;
	}
	if ((*temp)->left != NULL)
	{
		return tree_get_rightmost_node(&((*temp)->left));
	}
	temp = NULL;
	int temp2 = key_cmp((*dest)->key, key);
	while (temp2 != 0)
	{
		if (temp2 == -1)
		{
			dest = &((*dest)->left);
		}
		else
		{
			temp = dest;
			dest = &((*dest)->right);
		}
		temp2 = key_cmp((*dest)->key, key);
	}
	if (temp != NULL)
	{
		return temp;
	}
	else
	{
		return NULL;
	}
}

node** tree_get_next_node_by_key(node **dest, const void *key, int (*key_cmp)(const void*, const void*))
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	if ((*dest) == NULL)  // The tree is empty
	{
		return NULL;
	}
	node **temp = tree_get_node_by_key(dest, key, key_cmp);
	if (temp == NULL)  // The key is unused
	{
		return NULL;
	}
	if ((*temp)->right != NULL)
	{
		return tree_get_leftmost_node(&((*temp)->right));
	}
	temp = NULL;
	int temp2 = key_cmp((*dest)->key, key);
	while (temp2 != 0)
	{
		if (temp2 == -1)
		{
			temp = dest;
			dest = &((*dest)->left);
		}
		else
		{
			dest = &((*dest)->right);
		}
		temp2 = key_cmp((*dest)->key, key);
	}
	if (temp != NULL)
	{
		return temp;
	}
	else
	{
		return NULL;
	}
}
