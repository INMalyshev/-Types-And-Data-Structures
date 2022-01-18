#ifndef SHAPE_H
#define SHAPE_H

int get_choice(int minimum_value, int maximum_value);
void skip_stdin(void);
void menu(void);

#include "binary_tree.h"
#include "text_file.h"
#include "interior_hash_table.h"

typedef struct
{
  node_t *casual_tree;
  node_t *balanced_tree;
  table_t *table;
  text_file_t *text_file;
} structures_t;

int mainloop_iteration(structures_t *stuctures);
structures_t *index(char *filename);
void gen_stat(void);

#endif
