#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdio.h>

typedef struct
{
  void *data;
  void *previous;
} stack_note_t;

void free_stack_note_t(stack_note_t *note);

typedef struct
{
  size_t stack_len;
  stack_note_t *current_note;
} stack_t;

stack_t *new_stack_t(void);
void clear_stack_t(stack_t *stack);
int pop_stack_t(stack_t *stack);
stack_note_t *push_stack_t(stack_t *stack, void *data);
void print_stack_t(FILE *f, stack_t *stack, void printing_function (FILE*, void*));

void solve_case_stack_t(FILE *f, stack_t *stack);

#endif
