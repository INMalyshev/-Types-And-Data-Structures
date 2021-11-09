#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_stec.h"
#include "rc.h"
#include "mystring.h"

array_stec_t *new_array_stec_t(size_t nmemb)
{
  if (0 == nmemb) return NULL;

  array_stec_t *new = malloc(sizeof(array_stec_t));
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

void free_array_stec_t(array_stec_t* array_stec)
{
  for (void** p = array_stec->start_pointer; p < array_stec->end_pointer; p++)
  {
    free(*p);
    *p = NULL;
  }
  free(array_stec->start_pointer);
  free(array_stec);
}

int pop_array_stec_t(array_stec_t* array_stec)
{
  if (array_stec->start_pointer == array_stec->current_position_pointer)
    return STECK_IS_EMPTY;

  array_stec->current_position_pointer--;

  free(*array_stec->current_position_pointer);
  *array_stec->current_position_pointer = NULL;

  return OK;
}

int push_array_stec_t(array_stec_t* array_stec, void* data)
{
  if (array_stec->end_pointer == array_stec->current_position_pointer)
  {
    return STECK_IS_FULL;
  }

  *array_stec->current_position_pointer = data;
  array_stec->current_position_pointer++;

  return OK;
}

void print_array_stec_t(FILE* f, array_stec_t* array_stec, void printing_function (FILE*, void*))
{
  void **cp = array_stec->current_position_pointer - 1;

  for (;cp >= array_stec->start_pointer; cp--)
  {
    fprintf(f, "<%p> : ", *cp);
    printing_function(f, *cp);
  }
}

void solve_case_array_stec_t(FILE* f, array_stec_t* array_stec)
{
  void **cp = array_stec->current_position_pointer - 1;

  for (; cp >= array_stec->start_pointer; cp--)
  {
    for (int i = (int) strlen(((string_t*) (*cp))->string) - 1; i >= 0; i--)
      fprintf(f, "%c", ((string_t*) (*cp))->string[i]);
    fprintf(f, "\n");
  }
}
