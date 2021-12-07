#include <stdio.h>

#include "binary_tree.h"
#include "interior_hash_table.h"
#include "text_file.h"

int main(int argc, char **argv)
{
  setbuf(stdout, NULL);

  if (2 != argc)
  {
    printf("Wrong filename. Restart program\n");
    return 1;
  }

  printf("Reading text file.\n");

  tf_t tf;
  if (create_tf_t(argv[1], &tf))
  {
    printf("Something wrong with file. Restart program.\n");
    return 1;
  }

  pri_tf_t(&tf);

  printf("\n\nCreating interior hash table.\n");

  iht_t *iht = new_iht_t(tf.len);

  for (int i = 0; i < tf.len; i++)
  {
    add_iht_t(iht, tf.data[i]);
  }

  pri_iht_t(iht);

  printf("Creating binary tree.\n");

  bt_t *bt = new_bt_t();

  for (int i = 0; i < tf.len; i++)
  {
    add_bt_t(bt, tf.data[i]);
  }

  fix_height_bt_t(bt);
  pri_bt_t(bt);

  // printf("[DBG] HEIGHT : %d\n\n", get_height_bt_node_t(bt->root, -1));

  printf("\nDeleting elements.\n\n");

  del_bt_t(bt, 1);
  fix_height_bt_t(bt);
  pri_bt_t(bt);

  printf("\n\nSuccess!\n");

  return 0;
}
