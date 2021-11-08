#ifndef STEC_H
#define STEC_H

#include <stddef.h>
#include <stdio.h>

typedef struct
{
  void *data;
  void *previous;
} stec_note_t;

void free_stec_note_t(stec_note_t *note);

typedef struct
{
  size_t stec_len;
  stec_note_t *current_note;
} stec_t;

stec_t *new_stec_t(void);
void clear_stec_t(stec_t *stec);
int pop_stec_t(stec_t *stec);
stec_note_t *push_stec_t(stec_t *stec, void *data);
void print_stec_t(FILE *f, stec_t *stec, void printing_function (FILE*, void*));

#endif
