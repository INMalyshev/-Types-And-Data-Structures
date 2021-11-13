#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_stack.h"
#include "rc.h"
#include "mystring.h"

array_stack_t *new_array_stack_t(size_t nmemb)
{
  if (0 == nmemb) return NULL;

  array_stack_t *new = malloc(sizeof(array_stack_t));
  if (!new) return NULL;

  new->start_pointer = calloc(nmemb, sizeof(void*));
  if (!new->start_pointer)
  {
    free(new);

    return NULL;
  }

  new->end_pointer = new->start_pointer + nmemb;
  new->current_position_pointer = new->start_pointer;

  return new;
}

void free_array_stack_t(array_stack_t* array_stack)
{
  for (void** p = array_stack->start_pointer; p < array_stack->end_pointer; p++)
  {
    free(*p);
    *p = NULL;
  }
  free(array_stack->start_pointer);
  free(array_stack);
}

int pop_array_stack_t(array_stack_t* array_stack)
{
  if (array_stack->start_pointer == array_stack->current_position_pointer)
    return STACK_IS_EMPTY;

  array_stack->current_position_pointer--;

  free(*array_stack->current_position_pointer);
  *array_stack->current_position_pointer = NULL;

  return OK;
}

int push_array_stack_t(array_stack_t* array_stack, void* data)
{
  if (array_stack->end_pointer == array_stack->current_position_pointer)
  {
    return STACK_IS_FULL;
  }

  *array_stack->current_position_pointer = data;
  array_stack->current_position_pointer++;

  return OK;
}

void print_array_stack_t(FILE* f, array_stack_t* array_stack, void printing_function (FILE*, void*))
{
  void **cp = array_stack->current_position_pointer - 1;

  for (;cp >= array_stack->start_pointer; cp--)
  {
    fprintf(f, "<%p> : ", *cp);
    printing_function(f, *cp);
  }
}

void solve_case_array_stack_t(FILE* f, array_stack_t* array_stack)
{
  void **cp = array_stack->current_position_pointer - 1;

  for (; cp >= array_stack->start_pointer; cp--)
  {
    for (int i = (int) strlen(((string_t*) (*cp))->string) - 1; i >= 0; i--)
      fprintf(f, "%c", ((string_t*) (*cp))->string[i]);
    fprintf(f, "\n");
  }
}
