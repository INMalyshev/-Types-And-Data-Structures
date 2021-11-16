#ifndef SHAPE_H
#define SHAPE_H

#include "stack.h"
#include "array_stack.h"

typedef struct
{
  void **deallocated_memory;
  size_t len;
  size_t allocated;
} list_t;

int push_list_t(list_t*, void*);
void free_list_t(list_t*);
void print_list_t(list_t*);
list_t *new_list_t(void);

typedef struct
{
  stack_t *stack;
  list_t *stack_deallocated_memory;
  array_stack_t *array_stack;
  list_t *array_stack_deallocated_memory;
} base_t;

void skip_stdin(void);
void print_wellcome_menu(void);
int handle_manu(base_t *data_base);
void print_line(void);

#define ALLOCATION_INDEX_LIST_T 2
#define INITIAL_LIST_T_ALLOCATION 2

#define MAX_ARRAY_STACK_LEN 128

#define MAX_REPITIONS_AMOUNT 1000
#define MIN_REPITIONS_AMOUNT 1

#define MAX_STACK_LEN 1000
#define MIN_STACK_LEN 1

#define TEST_STRING "abcdefghijk"

#define STATISTICS_FILE_NAME "statistics.txt"
#define LINE_LEN 1024
typedef char line_t[LINE_LEN];

#define RUBBISH_FILE_NAME "rubbish.txt"

#endif
