#include <stddef.h>
#include <stdlib.h>

#include "array_queue.h"
#include "rc.h"

void free_array_queue_t(array_queue_t *array_queue)
{
  for (int i = 0; i < array_queue->len; i++)
    free(array_queue->data[i]);
  free(array_queue->data);
  free(array_queue);
}

void *pop_array_queue_t(array_queue_t *array_queue)
{
  if (0 == array_queue->len) return NULL;

  void* data = array_queue->data[0];

  for (int i = 0; i < array_queue->len - 1; i++)
    array_queue->data[i] = array_queue->data[i+1];

  array_queue->data[array_queue->len - 1] = NULL;
  array_queue->len--;

  return data;
}

int push_array_queue_t(array_queue_t *array_queue, void *data)
{
  if (array_queue->len >= ARRAY_QUEUE_LEN) return ERROR;

  array_queue->data[array_queue->len] = data;

  array_queue->len++;

  return OK;
}

array_queue_t* new_array_queue_t(void)
{
  array_queue_t *new = malloc(sizeof(array_queue_t));
  if (!new) return NULL;
  void **data = calloc(ARRAY_QUEUE_LEN, sizeof(void*));
  if (!data)
  {
    free(new);
    return NULL;
  }
  new->data = data;
  new->len = 0;

  return new;
}
