#ifndef BT_H
#define BT_H

typedef struct bt_node bt_node_t;
struct bt_node
{
  int value;
  bt_node_t *left;
  bt_node_t *right;
  int height;
  int count;
};

typedef struct bt bt_t;
struct bt
{
  bt_node_t *root;
};

void free_bt_node_t(bt_node_t *root);
void free_bt_t(bt_t *bt);
bt_node_t *find_bt_node_t(bt_node_t *root, int alpha, int *buf);
bt_node_t *new_bt_node_t(int alpha);
void add_bt_node_t(bt_node_t *root, int alpha);
void pri_bt_node_t(bt_node_t *root);
bt_t *new_bt_t(void);
void add_bt_t(bt_t *bt, int alpha);
void pri_bt_t(bt_t *bt);
bt_node_t* del_bt_node_t(bt_node_t *root, bt_node_t *current, int value, bt_t *tree);
void del_bt_t(bt_t *tree, int value);
int get_height_bt_node_t(bt_node_t *root, int s);
void fix_height_bt_node_t(bt_node_t *root, int s);
void fix_height_bt_t(bt_t *tree);

#endif
