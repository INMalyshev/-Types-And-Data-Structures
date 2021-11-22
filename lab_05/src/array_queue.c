#include <stddef.h>
#include <stdlib.h>

#include "array_queue.h"
#include "rc.h"

void free_array_queue_t(array_queue_t array_queue)
{
  for (size_t i = 0; i < ARRAY_QUEUE_LEN; i++)
    free(array_queue[i]);
  free(array_queue);
}

void *pop_array_queue_t(array_queue_t array_queue)
{
  void* data = array_queue[0];

  for (size_t i = 0; i < ARRAY_QUEUE_LEN - 1 && array_queue[i]; i++)
    array_queue[i] = (void*) array_queue[i+1];

  array_queue[ARRAY_QUEUE_LEN - 1] = NULL;

  return data;
}

int push_array_queue_t(array_queue_t array_queue, void *data)
{
  int complete = 0;

  for (size_t i = 0; i < ARRAY_QUEUE_LEN; i++)
  {
    if (!array_queue[i])
    {
      array_queue[i] = data;
      complete = 1;
      break;
    }
  }

  return !complete;
}

array_queue_t new_array_queue_t(void)
{
  array_queue_t array_queue = calloc(ARRAY_QUEUE_LEN, sizeof(void*));

  return array_queue;
}
