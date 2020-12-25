#ifndef __PRODUCT_H__
#define __PRODUCT_H__

typedef struct product_type pdata;

// pdata: __init__, __del__
extern pdata* pdata_create(const int, const int, const int);
extern int pdata_delete(pdata**);

// pdata: set
extern int pdata_set_id(pdata*, const int);
extern int pdata_set_price(pdata*, const int);
extern int pdata_set_amount(pdata*, const int);

// pdata: get
extern int pdata_get_id(const pdata*);
extern int pdata_get_price(const pdata*);
extern int pdata_get_amount(const pdata*);

// pdata: __key__
extern void* pdata_get_key(pdata*);

// pdata: __eq__
extern int pdata_cmp(const pdata*, const pdata*);

// pdata: __str__
extern const char* pdata_toString(const pdata*);

// pdata: display
extern int pdata_display(FILE*, const char*, const pdata*);

#endif
