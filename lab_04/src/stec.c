#include <stdlib.h>
#include <stdio.h>

#include "rc.h"
#include "stec.h"

stec_t *new_stec_t(void)
{
  stec_t *new = malloc(sizeof(stec_t));

  if (!new) return NULL;

  new->stec_len = 0;
  new->current_note = NULL;

  return new;
}

void clear_stec_t(stec_t *stec)
{
  for (; OK == pop_stec_t(stec););
}

int pop_stec_t(stec_t *stec)
{
  if (!stec->current_note)
    return STECK_IS_EMPTY;

  stec_note_t *new_current_note = stec->current_note->previous;
  free_stec_note_t(stec->current_note);

  stec->current_note = new_current_note;
  stec->stec_len--;

  return OK;
}

void free_stec_note_t(stec_note_t *note)
{
  free(note->data);
  free(note);
}

stec_note_t *push_stec_t(stec_t *stec, void *data)
{
  stec_note_t *new_current_note = malloc(sizeof(stec_note_t));
  if (!new_current_note) return NULL;

  new_current_note->previous = stec->current_note;
  new_current_note->data = data;

  stec->current_note = new_current_note;
  stec->stec_len++;

  return new_current_note;
}

void print_stec_t(FILE *f, stec_t *stec, void printing_function (FILE*, void*))
{
  for (stec_note_t *note = stec->current_note; note; note = note->previous)
  {
    fprintf(f, "<%p> : ", (void*) note->data);
    printing_function(f, note->data);
  }
}
