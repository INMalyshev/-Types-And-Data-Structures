#ifndef SHAPE_H
#define SHAPE_H

#include "stec.h"
#include "array_stec.h"

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
  stec_t *stec;
  list_t *stec_deallocated_memory;
  array_stec_t *array_stec;
  list_t *array_stec_deallocated_memory;
} base_t;

void skip_stdin(void);
void print_wellcome_menu(void);
int handle_manu(base_t *data_base);
void print_line(void);

#define ALLOCATION_INDEX_LIST_T 2
#define INITIAL_LIST_T_ALLOCATION 2

#define MAX_ARRAY_STEC_LEN 128

#define MAX_REPITIONS_AMOUNT 1000
#define MIN_REPITIONS_AMOUNT 1

#define MAX_STEC_LEN 1000
#define MIN_STEC_LEN 1

#define TEST_STRING "shlasashaposhosse"

#define LINE_LEN 1024
#define STATISTICS_FILE_NAME "statistics.txt"
typedef char line_t[LINE_LEN];

#endif
