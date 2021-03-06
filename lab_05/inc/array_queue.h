#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#define ARRAY_QUEUE_LEN 10001
typedef struct
{
  void **data;
  int len;
} array_queue_t;

void free_array_queue_t(array_queue_t *array_queue);
void *pop_array_queue_t(array_queue_t *array_queue);
int push_array_queue_t(array_queue_t *array_queue, void *data);
array_queue_t* new_array_queue_t(void);

#endif
