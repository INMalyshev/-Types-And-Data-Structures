#ifndef QUEUE_H
#define QUEUE_H

typedef struct
{
  void *queue_head;
} queue_t;

typedef struct
{
  void *previous_note;
  void *data;
} queue_note_t;

void free_queue_t(queue_t *queue);
queue_note_t *pop_queue_t(queue_t *queue);
int push_queue_t(queue_t *queue, void *data);
queue_note_t *new_queue_note_t(void *data);
void free_queue_note_t(queue_note_t *queue_note);

void *simulate_with_queue(void);

#endif
