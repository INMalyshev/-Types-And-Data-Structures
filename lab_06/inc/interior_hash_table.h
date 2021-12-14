#ifndef table_H
#define table_H

#define ALLOCATION_FACTOR 2

typedef struct element element_t;
struct element
{
  int value;
  int free;
};

typedef struct table table_t;
struct table
{
  element_t *data;
  int allocated;
  int elem_amount;
  int factor_number;
  int collision;
};

table_t *new_table_t(int nmemb);
table_t *add_table_t(table_t *table, int alpha);
void free_table_t(table_t *table);
void pri_table_t(table_t *table);
element_t *find_table_t(table_t *table, int alpha, int *buf);
void del_table_t(table_t *table, int alpha, int *buf);
table_t *refactor_table_t(table_t *table);

#endif
