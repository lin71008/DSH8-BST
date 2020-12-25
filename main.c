#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <unistd.h>

#include "functional.h"
#include "product_list.h"

int main(int argc, char const *argv[])
{
	node *tree = NULL;
	char k='\0';
	menu();
	while (k != 'q')
	{
		k = getch();
		system("cls");
		if (k == '1')
		{
			search_product(&tree);
		}
		else if (k == '2')
		{
			import_product(&tree);
		}
		else if (k == '3')
		{
			delete_product(&tree);
		}
		else if (k == '4')
		{
			export_product(&tree);
		}
		else if (k == '5')
		{
			display_product(&tree);
		}
		else if (k == '6')
		{
			highest_price_product(&tree);
		}
		else if (k == '7')
		{
			modify_product(&tree);
		}
		else if (k == '8')
		{
			file_io(&tree);
		}
		else
		{
			menu();
		}
	}
	product_tree_delete(&tree);
	return 0;
}
