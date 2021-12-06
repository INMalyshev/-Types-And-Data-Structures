#ifndef IHT_H
#define IHT_H

#define ALLOCATION_FACTOR 2

typedef struct iht_elem iht_elem_t;
struct iht_elem
{
  int value;
  int free;
};

typedef struct iht iht_t;
struct iht
{
  iht_elem_t *data;
  int allocated;
  int elem_amount;
  int factor_number;
};

iht_t *new_iht_t(int nmemb);
iht_t *add_iht_t(iht_t *iht, int alpha);
void free_iht_t(iht_t *iht);
void pri_iht_t(iht_t *iht);
iht_elem_t *find_iht_t(iht_t *iht, int alpha, int *buf);
void del_iht_t(iht_t *iht, int alpha, int *buf);
iht_t *refactor_iht_t(iht_t *iht);

#endif
