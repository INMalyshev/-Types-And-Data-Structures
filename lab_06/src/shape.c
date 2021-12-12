#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "shape.h"

int get_choice(int minimum_value, int maximum_value)
{
  int choice;
  int got_choice = 0;

  while (!got_choice)
  {
    printf("Input integer from %d to %d:\n", minimum_value, maximum_value);

    if (!scanf("%d", &choice))
    {
      printf("Wrong input. Try again.");
      skip_stdin();
      continue;
    }

    if (choice < minimum_value || choice > maximum_value)
    {
      printf("Wrong input. Try again.");
      skip_stdin();
      continue;
    }

    got_choice = 1;
  }

  return choice;
}

void skip_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

void menu(void)
{
  printf("+--------------------------------------------------------------------+\n");
  printf("  1. Insert element;\n");
  printf("  2. Find element;\n");
  printf("  3. Remove element;\n");
  printf("\n");
  printf("  4. Print structures;\n");
  printf("\n");
  printf("  0. Exit.\n");
  printf("+--------------------------------------------------------------------+\n");
}

structures_t *index(char *filename)
{
  printf("Reading text file <%s>.\n", filename);

  text_file_t *text_file = create_text_file_t(filename);
  if (!text_file)
  {
    printf("Wrong file(name). Restart program.\n");
    return NULL;
  }

  tree_t *casual_tree = new_tree_t();
  node_t *balanced_tree = NULL;
  table_t *hash_table = new_table_t(text_file->len);

  for (int i = 0; i < text_file->len; i++)
  {
    add_tree_t(casual_tree, text_file->data[i]);
    balanced_tree = insert(balanced_tree, text_file->data[i]);
    hash_table = add_table_t(hash_table, text_file->data[i]);
  }

  structures_t *structures = malloc(sizeof(structures_t));
  structures->casual_tree = casual_tree;
  structures->balanced_tree = balanced_tree;
  structures->table = hash_table;
  structures->text_file = text_file;

  return structures;
}

int mainloop_iteration(structures_t *structures)
{
  // if (structures)
  //   printf("init ---> all right\n");

  menu();

  int choice = get_choice(0, 4);

  switch (choice)
  {
    case 1:
    {
      printf("Insert.\n\n");
      printf("Input key:\n");
      // int key = get_choice(INT_MIN, INT_MAX);
      break;
    };
    case 2:
    {
      printf("Find.\n\n");
      break;
    };
    case 3:
    {
      printf("Remove.\n\n");
      break;
    };
    case 4:
    {
      printf("Print.\n\n");
      pri_tree_t(structures->casual_tree);
      printf("\nBalanced binary search tree prefix form:\n\n");
      pri_node_t(structures->balanced_tree);
      pri_table_t(structures->table);
      pri_text_file_t(structures->text_file);
      break;
    };
  }

  return choice;
}
