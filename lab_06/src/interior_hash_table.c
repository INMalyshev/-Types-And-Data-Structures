#include <stdlib.h>
#include <stdio.h>

#include "interior_hash_table.h"

iht_t *new_iht_t(int nmemb)
{
  iht_t *iht = malloc(sizeof(iht_t));

  iht->data = calloc(nmemb, sizeof(iht_elem_t));
  iht->allocated = nmemb;
  iht->elem_amount = 0;
  iht->factor_number = nmemb;

  return iht;
}

iht_t *add_iht_t(iht_t *iht, int alpha)
{
  if (iht->elem_amount < iht->allocated)
  {
    int index = alpha % iht->factor_number;
    for (int j = 0; j < iht->allocated; j++)
    {
      int i = (index + j) % iht->factor_number;
      if (iht->data[i].free)
      {
        iht->data[i].value = alpha;
        iht->data[i].free = 0;
        iht->elem_amount++;
      }
    }
  }
  else
  {
    iht = refactor_iht_t(iht);
    add_iht_t(iht, alpha);
  }
  return iht;
}

void free_iht_t(iht_t *iht)
{
  free(iht->data);
  free(iht);
}

void pri_iht_t(iht_t *iht)
{
  printf("Interior hash table:\n\n");
  if (0 == iht->elem_amount)
  {
    printf("Empty interior hash table.\n\n");
    return;
  }
  for (int i = 0; i < iht->allocated; i++)
  {
    if (!iht->data[i].free)
    {
      printf("<index: %d> <value: %d>\n", i, iht->data[i].value);
    }
  }
  printf("\n");
}

iht_elem_t *find_iht_t(iht_t *iht, int alpha, int *buf)
{
  int counter = 0;
  int index = alpha % iht->factor_number;
  for (int j = 0; j < iht->allocated; j++)
  {
    counter++;
    int i = (index + j) % iht->factor_number;
    if (!iht->data[i].free && alpha == iht->data[i].value)
    {
      *buf = counter;
      return &(iht->data[i]);
    }
  }
  *buf = counter;
  return NULL;
}

void del_iht_t(iht_t *iht, int alpha, int *buf)
{
  iht_elem_t *elem = find_iht_t(iht, alpha, buf);
  if (!elem)
  {
    printf("Element is not found.\n");
    return;
  }
  elem->free = 1;
}

iht_t *refactor_iht_t(iht_t *iht)
{
  iht_t *new = new_iht_t(iht->allocated * ALLOCATION_FACTOR);
  for (int i = 0; i < iht->allocated; i++)
  {
    if (!iht->data[i].free)
    {
      add_iht_t(new, iht->data[i].value);
    }
  }
  free_iht_t(iht);
  return new;
}
