#include <stdio.h>
#include <stdlib.h>

#include "product.h"

struct product_type
{
	int id, price, amount;
};

pdata* pdata_create(const int id, const int price, const int amount)
{
	pdata *ret = (pdata*) malloc(sizeof(pdata));
	if (ret == NULL)  // RuntimeError, can not allocate new pdata
	{
		return NULL;
	}
	ret->id = id;
	ret->price = price;
	ret->amount = amount;
	return ret;
}

int pdata_delete(pdata **dest)
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	if ((*dest) == NULL)  // The pdata is empty
	{
		return 0;
	}
	free((*dest));
	(*dest) = NULL;
	return 0;
}

int pdata_set_id(pdata *dest, const int id)
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		dest->id = id;
		return 0;
	}
}

int pdata_set_price(pdata *dest, const int price)
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		dest->price = price;
		return 0;
	}
}

int pdata_set_amount(pdata *dest, const int amount)
{
	if (dest == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		dest->amount = amount;
		return 0;
	}
}

int pdata_get_id(const pdata *source)
{
	if (source == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		return source->id;
	}
}

int pdata_get_price(const pdata *source)
{
	if (source == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		return source->price;
	}
}

int pdata_get_amount(const pdata *source)
{
	if (source == NULL)  // Undefined behavior
	{
		return -1;
	}
	else
	{
		return source->amount;
	}
}

void* pdata_get_key(pdata *dest)
{
	if (dest == NULL)  // Undefined behavior
	{
		return NULL;
	}
	else
	{
		return ((void*) &(dest->id));
	}
}

int pdata_cmp(const pdata *p1, const pdata *p2)
{
	if (p1 == NULL || p2 == NULL)  // Undefined behavior
	{
		return 0;
	}
	else
	{
		return (p1->id == p2->id) && (p1->price == p2->price);
	}
}

const char* pdata_toString(const pdata *source)
{
	if (source == NULL)  // Undefined behavior
	{
		return NULL;
	}
	char *buffer = (char*) malloc(64*sizeof(char));
	sprintf(buffer, "product number: %03d, price: %d, amount: %d", source->id, source->price, source->amount);
	return buffer;
}

int pdata_display(FILE *fp, const char *format, const pdata *source)
{
	if (source == NULL || format == NULL || fp == NULL)  // Undefined behavior
	{
		return -1;
	}
	fprintf(fp, format, source->id, source->price, source->amount);
	return 0;
}
