#ifndef ARRAY_STEC_H
#define ARRAY_STEC_H

#include <stddef.h>
#include <stdio.h>

typedef struct
{
  void **start_pointer;
  void **end_pointer;
  void **current_position_pointer;
} array_stec_t;

array_stec_t *new_array_stec_t(size_t nmemb);
void free_array_stec_t(array_stec_t* array_stec);
int pop_array_stec_t(array_stec_t* array_stec);
int push_array_stec_t(array_stec_t* array_stec, void* data);
void print_array_stec_t(FILE* f, array_stec_t* array_stec, void printing_function (FILE*, void*));

void solve_case_array_stec_t(FILE* f, array_stec_t* array_stec);

#endif
