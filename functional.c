#include <stdio.h>

#include <conio.h>
#include <unistd.h>

#include "functional.h"

#include "product.h"
#include "product_list.h"
#include "ui.h"

#define FILE_IO_FORMAT "%d %d %d\n"
#define TERMIAL_O_FORMAT "product number: %03d, price: %d, amount: %d\n"

void menu()
{
	main_menu();
}

void import_product(node **dest)
{
	int id, price, amount;
	import_menu();
	printf("\nProduct number, Amount: ");
	scanf("%d%d", &id, &amount);
	pdata *p = product_tree_get_pdata_by_key(dest, id);
	if (p == NULL)
	{
		printf("The product you want to insert is not in the database.\n");
		printf("Please input the price:");
		scanf("%d", &price);
		p = pdata_create(id, price, amount);
		printf("=== you have inserted ===\n");
		printf("%s\n", pdata_toString(p));
		product_tree_add_pdata(dest, p);
		printf("=== into the tree ===\n");
	}
	else
	{
		printf("%s\n", pdata_toString(p));
		printf("=== inserted ===\n");
		pdata_set_amount(p, pdata_get_amount(p)+amount);
		printf("%s\n", pdata_toString(p));
	}
}

void export_product(node **dest)
{
	int id, amount;
	export_menu();
	printf("\nProduct number, Amount: ");
	scanf("%d%d", &id, &amount);
	pdata *p = product_tree_get_pdata_by_key(dest, id);
	if (p != NULL)
	{
		if (pdata_get_amount(p) > amount)
		{
			printf("=== you have just export ===\n");
			printf("%s\n", pdata_toString(p));
			pdata_set_amount(p, pdata_get_amount(p)-amount);
			printf("=== remains ===\n");
			printf("%s\n", pdata_toString(p));
		}
		else if (pdata_get_amount(p) == amount)
		{
			printf("=== you have just export ===");
			printf("%s\n", pdata_toString(p));
#ifndef AutoRemove
			printf("=== remains ===\n");
			pdata_set_amount(p, pdata_get_amount(p)-amount);
			printf("%s\n", pdata_toString(p));
#else
			printf("=== The product remain amount equal to zero ===\n");
			printf("=== Delete the product from the tree ===\n");
			product_tree_remove_node_by_key(dest, id);
#endif
		}
		else
		{
			printf("The product you want to export is not enough in database.\n");
		}
	}
	else
	{
		printf("The product you want to export is not exists in database.\n");
	}
}

void delete_product(node **dest)
{
	int id;
	delete_menu();
	printf("\nProduct number: ");
	scanf("%d", &id);
	const pdata *p = product_tree_get_pdata_by_key(dest, id);
	if (p != NULL)
	{
		printf("=== you have just deleted===\n");
		printf("%s\n", pdata_toString(p));
		product_tree_remove_node_by_key(dest, id);
	}
	else
	{
		printf("The product you want to delete is not exists in database.\n");
	}
}

void search_product(node **dest)
{
	int id;
	search_menu();
	printf("\nProduct number: ");
	scanf("%d", &id);
	const pdata *p = product_tree_get_pdata_by_key(dest, id);
	if (p != NULL)
	{
		printf("%s\n", pdata_toString(p));
		char k;
		k = getch();
		while (k != 'r')
		{
			if (k == 'p')
			{
				node **temp = product_tree_get_previous_node_by_key(dest, id);
				if (temp != NULL)
				{
					id = product_tree_node_get_key(*temp);
					p = product_tree_node_get_value(*temp);
					printf("%s\n", pdata_toString(p));
				}
				else
				{
					printf("Already at the front of the database.\n");
				}
			}
			else if (k == 'n')
			{
				node **temp = product_tree_get_next_node_by_key(dest, id);
				if (temp != NULL)
				{
					id = product_tree_node_get_key(*temp);
					p = product_tree_node_get_value(*temp);
					printf("%s\n",pdata_toString(p));
				}
				else
				{
					printf("Already at the tail of the database.\n");
				}
			}
			k = getch();
		}
		printf("Return to the menu.\n");
	}
	else
	{
		printf("The product you want to search is not exists in database.\n");
	}
}

void display_product(node **dest)
{
	list_menu();
	if (product_tree_display(stdout, TERMIAL_O_FORMAT, *dest) != 0)
	{
		printf("The database is empty.\n");
	}
}

void highest_price_product(node **dest)
{
	highest_menu();
	node *temp = product_tree_get_highest_price_node(dest);
	if (temp != NULL)
	{
		product_tree_display(stdout, TERMIAL_O_FORMAT, temp);
	}
	else
	{
		printf("The database is empty.\n");
	}
}

void modify_product(node **dest)
{
	modify_menu();
	int id, value;
	printf("\nProduct number: ");
	scanf("%d", &id);
	pdata *p = product_tree_get_pdata_by_key(dest, id);
	if (p == NULL)
	{
		printf("The product you want to modify is not in the database.\n");
	}
	else
	{
		printf("%s\n", pdata_toString(p));
		modify_select_menu();
		char k = getch();
		while (k != '0')
		{
			if (k == '1')
			{
				printf("new product number: ");
				scanf("%d", &value);
				if (product_tree_get_pdata_by_key(dest, value) != NULL)
				{
					printf("Already in used.\n");
				}
				else
				{
					p = pdata_create(value, pdata_get_price(p), pdata_get_amount(p));
					product_tree_add_pdata(dest, p);
					product_tree_remove_node_by_key(dest, id);
				}
			}
			else if (k == '2')
			{
				printf("Set product price to: ");
				scanf("%d", &value);
				pdata_set_price(p, value);
			}
			else if (k == '3')
			{
				printf("Set product amount to: ");
				scanf("%d", &value);
				pdata_set_amount(p, value);
#ifdef AutoRemove
				if (value == 0)
				{
					product_tree_remove_node_by_key(dest, id);
				}
#endif
			}
			modify_select_menu();
			k = getch();
		}
		printf("Return to menu\n");
	}
}

void file_io(node **dest)
{
	file_io_menu();
	char k;
	k = getch();
	while (k != '0')
	{
		if (k == '1')
		{
			import_file_menu();
			char file_name[64];
			printf("\nFile name: ");
			scanf("%s", file_name);
			FILE *fp = fopen(file_name, "r");
			if (fp != NULL)
			{
				fseek(fp, 0, SEEK_END);
				int file_size = ftell(fp);
				if (file_size == 0)
				{
					printf("Error: file: %s is empty\n", file_name);
					fclose(fp);
					break;
				}
				fseek(fp, 0, SEEK_SET);
				char *line_buffer = NULL;
			  	size_t line_buffer_size = 0;
				ssize_t line_size;
				line_size = getline(&line_buffer, &line_buffer_size, fp);
				while (line_size >= 0)
				{
					int id, price, amount;
					if (sscanf(line_buffer, FILE_IO_FORMAT, &id, &price, &amount) == 3)
					{
						pdata *p = product_tree_get_pdata_by_key(dest, id);
						if (p == NULL)
						{
							p = pdata_create(id, price, amount);
							printf("Import new product: %s\n", pdata_toString(p));
							product_tree_add_pdata(dest, p);
						}
						else
						{
							pdata_set_amount(p, pdata_get_amount(p)+amount);
							printf("Import product: %s\n", pdata_toString(p));
						}
					}
					line_size = getline(&line_buffer, &line_buffer_size, fp);
				}
				fclose(fp);
			}
			else
			{
				printf("Error: file: %s did not exist.\n", file_name);
			}
			file_io_menu();
		}
		else if (k == '2')
		{
			export_file_menu();
			char file_name[64];
			printf("\nFile name: ");
			scanf("%s", file_name);
			FILE *fp = fopen(file_name, "w");
			if (fp != NULL)
			{
				product_tree_display(fp, FILE_IO_FORMAT, *dest);
				fclose(fp);
			}
		file_io_menu();
		}
		k = getch();
	}
	printf("Return to menu\n");
}
