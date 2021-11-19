#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "rc.h"

int push_queue_t(queue_t *queue, void *data)
{
  queue_note_t *new_note = new_queue_note_t(data);
  if (!new_note) return ERROR;

  new_note->previous_note = queue->queue_head;
  queue->queue_head = new_note;

  return OK;
}

queue_note_t *pop_queue_t(queue_t *queue)
{
  queue_note_t *note = queue->queue_head;

  if (!note) return note;

  queue->queue_head = note->previous_note;

  return note;
}

void free_queue_t(queue_t *queue)
{
  void* note;

  while ((note = pop_queue_t(queue)))
    free_queue_note_t(note);
}

queue_note_t *new_queue_note_t(void *data)
{
  queue_note_t *note = calloc(1, sizeof(queue_note_t));
  if (!note) return NULL;

  note->data = data;

  return note;
}

void free_queue_note_t(queue_note_t *queue_note)
{
  free(queue_note->data);
  free(queue_note);
}