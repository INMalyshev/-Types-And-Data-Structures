#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rc.h"
#include "stack.h"
#include "mystring.h"

stack_t *new_stack_t(void)
{
  stack_t *new = malloc(sizeof(stack_t));

  if (!new) return NULL;

  new->stack_len = 0;
  new->current_note = NULL;

  return new;
}

void clear_stack_t(stack_t *stack)
{
  for (; OK == pop_stack_t(stack););
}

int pop_stack_t(stack_t *stack)
{
  if (!stack->current_note)
    return STACK_IS_EMPTY;

  stack_note_t *new_current_note = stack->current_note->previous;
  free_stack_note_t(stack->current_note);

  stack->current_note = new_current_note;
  stack->stack_len--;

  return OK;
}

void free_stack_note_t(stack_note_t *note)
{
  free(note->data);
  free(note);
}

stack_note_t *push_stack_t(stack_t *stack, void *data)
{
  stack_note_t *new_current_note = malloc(sizeof(stack_note_t));
  if (!new_current_note) return NULL;

  new_current_note->previous = stack->current_note;
  new_current_note->data = data;

  stack->current_note = new_current_note;
  stack->stack_len++;

  return new_current_note;
}

void print_stack_t(FILE *f, stack_t *stack, void printing_function (FILE*, void*))
{
  for (stack_note_t *note = stack->current_note; note; note = note->previous)
  {
    fprintf(f, "<%p> : ", (void*) note->data);
    printing_function(f, note->data);
  }
}

void solve_case_stack_t(FILE *f, stack_t *stack)
{
  if (!stack->current_note)
    return;

  stack_note_t *current_note = stack->current_note;

  while (current_note)
  {
    for (int i = (int) strlen(((string_t*) current_note->data)->string) - 1; i >= 0; i--)
      fprintf(f, "%c", ((string_t*) current_note->data)->string[i]);
    fprintf(f, "\n");

    current_note = current_note->previous;
  }
}
