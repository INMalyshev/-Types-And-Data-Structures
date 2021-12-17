#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>


#include "shape.h"
#include "tick.h"

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
  printf("  5. Refactor hash table;\n");
  printf("\n");
  printf("  6. Generate statistics;\n");
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

  node_t *casual_tree = NULL;
  node_t *balanced_tree = NULL;
  table_t *hash_table = new_table_t(3);

  for (int i = 0; i < text_file->len; i++)
  {
    casual_tree = insert(casual_tree, text_file->data[i], 0);
    balanced_tree = insert(balanced_tree, text_file->data[i], 1);
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

  int choice = get_choice(0, 6);

  switch (choice)
  {
    case 1:
    {
      printf("Insert.\n\n");
      printf("Input key:\n");
      int key = get_choice(INT_MIN, INT_MAX);

      uint64_t t1, t2;

      // int buf = 0;
      printf("\nCasual binary tree:\n");
      t1 = tick();
      structures->casual_tree = insert(structures->casual_tree, key, 0);
      // if (!result) printf("Nothing found.\n");
      // printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      // buf = 0;
      printf("\nBalanced binary tree:\n");
      t1 = tick();
      structures->balanced_tree = insert(structures->balanced_tree, key, 1);
      // if (!result) printf("Nothing found.\n");
      // printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      // buf = 0;
      printf("\nInterior hash table:\n");
      t1 = tick();
      structures->table = add_table_t(structures->table, key);
      // if (!res) printf("Nothing found.\n");
      // printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      // buf = 0;
      printf("\nText file:\n");
      t1 = tick();
      insert_text_file_t(structures->text_file, key);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      break;
    };
    case 2:
    {
      printf("Find.\n\n");
      printf("Input key:\n");
      int key = get_choice(INT_MIN, INT_MAX);

      uint64_t t1, t2;

      int buf = 0;
      printf("\nCasual binary tree:\n");
      t1 = tick();
      node_t *result = find_node_t(structures->casual_tree, key, &buf);
      if (!result) printf("Nothing found.\n");
      // printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      buf = 0;
      printf("\nBalanced binary tree:\n");
      t1 = tick();
      result = find_node_t(structures->balanced_tree, key, &buf);
      if (!result) printf("Nothing found.\n");
      // printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      buf = 0;
      printf("\nInterior hash table:\n");
      t1 = tick();
      element_t *res = find_table_t(structures->table, key, &buf);
      if (!res) printf("Nothing found.\n");
      printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      buf = 0;
      printf("\nText file:\n");
      t1 = tick();
      find_text_file_t(structures->text_file, key);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      break;
    };
    case 3:
    {
      printf("Remove.\n\n");
      printf("Input key:\n");
      int key = get_choice(INT_MIN, INT_MAX);

      uint64_t t1, t2;
      int buf = 0;

      printf("\nCasual binary tree:\n");
      t1 = tick();
      structures->casual_tree = delete(structures->casual_tree, key, 0);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      printf("\nBalanced binary tree:\n");
      t1 = tick();
      structures->balanced_tree = delete(structures->balanced_tree, key, 1);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      printf("\nInterior hash table:\n");
      t1 = tick();
      del_table_t(structures->table, key, &buf);
      printf("Comparison amount: %d\n", buf);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      printf("\nText file:\n");
      t1 = tick();
      delete_text_file_t(structures->text_file, key);
      t2 = tick();
      printf("Processor run time ---> %" PRIu64 " ticks\n", t2 - t1);

      break;
    };
    case 4:
    {
      printf("Print.\n\n");
      printf("\nCasual binary search tree prefix form:\n\n");
      pri_node_t(structures->casual_tree, 0);
      printf("\nBalanced binary search tree prefix form:\n\n");
      pri_node_t(structures->balanced_tree, 0);
      pri_table_t(structures->table);
      pri_text_file_t(structures->text_file);
      break;
    };
    case 5:
    {
      printf("Refactor hash table.\n\n");
      structures->table = refactor_table_t(structures->table);
      printf("Ok.\n\n");
      break;
    }
    case 6:
    {
      gen_stat();
      break;
    }
  }

  return choice;
}

void gen_stat(void)
{
  printf("Enter initial element amount:\n");
  int len = get_choice(0, 200);

  node_t *bt = NULL;
  node_t *bbt = NULL;
  table_t *table = new_table_t(len+1);
  text_file_t tf = {"test.txt", len + 1, malloc(len*sizeof(int))};

  for (int i = 0; i < len; i++)
  {
    bt = insert(bt, rand()%100, 0);
    bbt = insert(bbt, rand()%100, 1);
    table = add_table_t(table, rand()%100);
    tf.data[i] = rand()%100;
  }

  uint64_t t1, t2;
  uint64_t ia = 0, ra = 0, ib = 0, rb = 0, ic = 0, rc = 0, id = 0, rd = 0;

  int buf = 0;

  for (int i = 0; i < 100; i++)
  {
    t1 = tick();
    bt = insert(bt, rand()%100, 0);
    t2 = tick();
    ia += t2 - t1;

    t1 = tick();
    bt = delete(bt, rand()%100, 0);
    t2 = tick();
    ra += t2 - t1;

    t1 = tick();
    bbt = insert(bbt, rand()%100, 1);
    t2 = tick();
    ib += t2 - t1;

    t1 = tick();
    bbt = delete(bbt, rand()%100, 1);
    t2 = tick();
    rb += t2 - t1;

    t1 = tick();
    table = add_table_t(table, rand()%100);
    t2 = tick();
    ic += t2 - t1;

    t1 = tick();
    del_table_t(table, rand()%100, &buf);
    t2 = tick();
    rc += t2 - t1;

    t1 = tick();
    insert_text_file_t(&tf, rand()%100);
    t2 = tick();
    id += t2 - t1;

    t1 = tick();
    delete_text_file_t(&tf, rand()%100);
    t2 = tick();
    rd += t2 - t1;
  }

  printf("Binary tree size:          %lld\n", sizeof(node_t) * len);
  printf("Balanced binary tree size: %lld\n", sizeof(node_t) * len);
  printf("Hash table size:           %lld\n", sizeof(element_t) * table->factor_number + sizeof(table_t));
  printf("File data size:            %lld\n", sizeof(int) * len + sizeof(text_file_t));

  printf("\n");
  printf("Binary tree:\n");
  printf("Insert: %"PRIu64" ticks\n", ia/100);
  printf("Remove: %"PRIu64" ticks\n", ra/100);
  printf("\n");
  printf("Balanced binary tree:\n");
  printf("Insert: %"PRIu64" ticks\n", ib/100);
  printf("Remove: %"PRIu64" ticks\n", rb/100);
  printf("\n");
  printf("Interior hash table:\n");
  printf("Insert: %"PRIu64" ticks\n", ic/100);
  printf("Remove: %"PRIu64" ticks\n", rc/100);
  printf("\n");
  printf("Text file:\n");
  printf("Insert: %"PRIu64" ticks\n", id/100);
  printf("Remove: %"PRIu64" ticks\n", rd/100);

  free_node_t(bt);
  free_node_t(bbt);
  free_table_t(table);
  free(tf.data);
}
