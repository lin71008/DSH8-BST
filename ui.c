// auto generator by text-gen.exe
#include <stdio.h>

#include "ui.h"

void main_menu(void)
{
	printf("=== Menu ===\n");
	printf("[1] Search product\n");
	printf("[2] Import product\n");
	printf("[3] Delete product\n");
	printf("[4] Export product\n");
	printf("[5] List in order\n");
	printf("[6] Modify product information\n");
	printf("[7] File I/O\n");
	printf("[q] Quit\n");
}

void search_menu(void)
{
	printf("=== Search for a product by the product number ===\n");
	printf("Read in the product number and show all of the information of the product if the\n");
	printf("product is found.\n");
	printf("Press \"N\" key to show the next product information in increasing order of\n");
	printf("product number, press \"P\" key to show the previous product information in\n");
	printf("increasing order of product number, press \"R\" key to return.\n");
}

void import_menu(void)
{
	printf("=== Import product ===\n");
	printf("Read in the product number and the amount.\n");
	printf("If the product exists, the amount of the product is increased. Otherwise, insert\n");
	printf("the product into the tree.\n");
}

void delete_menu(void)
{
	printf("=== Delete product ===\n");
	printf("Read in the product number and delete the product from the tree if the product\n");
	printf("is found.\n");
}

void export_menu(void)
{
	printf("=== Export product ===\n");
	printf("Read in the product number and the amount.\n");
	printf("The amount of the product is decreased if the product is found and the amount is\n");
	printf("enough.\n");
	printf("Show error message if the amount is not enough.\n");
}

void list_menu(void)
{
	printf("=== List all product information in increasing order of product number. ===\n");
}

void modify_menu(void)
{
	printf("=== Modify product information ===\n");
	printf("Read in product number, the component would to modify and it's new value.\n");
	printf("If the product exists, modify the product information as given.\n");
}

void modify_select_menu(void)
{
	printf("=== Modify ... ? ===\n");
	printf("[1] Modify product number\n");
	printf("[2] Modify product price\n");
	printf("[3] Modify product amount\n");
	printf("[0] Return to menu\n");
}

void file_io_menu(void)
{
	printf("=== Import/Export product information from/to file. ===\n");
	printf("[1] Import product information from file\n");
	printf("[2] Export product information to file\n");
	printf("[0] Return to menu\n");
}

void import_file_menu(void)
{
	printf("=== Import product information from file. ===\n");
}

void export_file_menu(void)
{
	printf("=== Export all product information to file. ===\n");
}

void highest_menu(void)
{
	printf("=== The product number with highest price ===\n");
}
