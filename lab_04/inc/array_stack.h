#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stddef.h>
#include <stdio.h>

typedef struct
{
  void **start_pointer;
  void **end_pointer;
  void **current_position_pointer;
} array_stack_t;

array_stack_t *new_array_stack_t(size_t nmemb);
void free_array_stack_t(array_stack_t* array_stack);
int pop_array_stack_t(array_stack_t* array_stack);
int push_array_stack_t(array_stack_t* array_stack, void* data);
void print_array_stack_t(FILE* f, array_stack_t* array_stack, void printing_function (FILE*, void*));

void solve_case_array_stack_t(FILE* f, array_stack_t* array_stack);

#endif
