#ifndef __FUNCTIONAL_H__
#define __FUNCTIONAL_H__

typedef struct node node;

// menu
extern void menu();

// import product
extern void import_product(node**);

// export product
extern void export_product(node**);

// delete product
extern void delete_product(node**);

// search product
extern void search_product(node**);

// display product
extern void display_product(node**);

// modify product
extern void modify_product(node**);

// file io
extern void file_io(node**);

// highest price product
extern void highest_price_product(node**);

#endif
