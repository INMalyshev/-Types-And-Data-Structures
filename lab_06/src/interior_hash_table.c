#include <stdlib.h>
#include <stdio.h>

#include "interior_hash_table.h"

table_t *new_table_t(int nmemb)
{
  table_t *table = malloc(sizeof(table_t));
  if (nmemb <= 0) nmemb = 10;

  table->data = malloc(nmemb * sizeof(element_t));
  table->allocated = nmemb;
  table->elem_amount = 0;
  table->factor_number = nmemb;
  table->collision = 0;

  for (int i = 0; i < table->allocated; i++)
  {
    table->data[i].free = 1;
  }

  return table;
}

table_t *add_table_t(table_t *table, int alpha)
{
  if (table->elem_amount < table->allocated)
  {
    int index = alpha % table->factor_number;

    if (!table->data[index].free)
      table->collision += 1;

    for (int j = 0; j < table->allocated; j++)
    {
      int i = (index + j) % table->factor_number;
      if (table->data[i].free)
      {
        table->data[i].value = alpha;
        table->data[i].free = 0;
        table->elem_amount += 1;
        break;
      }
    }
  }
  else
  {
    table = refactor_table_t(table);
    add_table_t(table, alpha);
  }
  return table;
}

void free_table_t(table_t *table)
{
  free(table->data);
  free(table);
}

void pri_table_t(table_t *table)
{
  printf("\nInterior hash table:\n\n");
  if (0 == table->elem_amount)
  {
    printf("Empty interior hash table.\n\n");
    return;
  }
  printf("Collision: %d (%.1lf%%)\n", table->collision, (double) table->collision / table->elem_amount *100);
  for (int i = 0; i < table->allocated; i++)
  {
    if (!table->data[i].free)
    {
      printf("<index: %d> <value: %d>\n", i, table->data[i].value);
    }
  }
  printf("\n");
}

element_t *find_table_t(table_t *table, int alpha, int *buf)
{
  int counter = 0;
  int index = alpha % table->factor_number;
  for (int j = 0; j < table->allocated; j++)
  {
    counter++;
    int i = (index + j) % table->factor_number;
    if (!table->data[i].free && alpha == table->data[i].value)
    {
      *buf = counter;
      return &(table->data[i]);
    }
  }
  *buf = counter;
  return NULL;
}

void del_table_t(table_t *table, int alpha, int *buf)
{
  element_t *elem = find_table_t(table, alpha, buf);
  if (!elem)
  {
    // printf("Nothing found.\n");
    return;
  }

  int index = alpha % table->factor_number;

  if (!table->data[index].free && table->data[index].value != alpha)
    table->collision -= 1;

  elem->free = 1;
}

table_t *refactor_table_t(table_t *table)
{
  table_t *new = new_table_t(table->allocated * ALLOCATION_FACTOR);
  for (int i = 0; i < table->allocated; i++)
  {
    if (!table->data[i].free)
    {
      add_table_t(new, table->data[i].value);
    }
  }
  free_table_t(table);
  return new;
}
