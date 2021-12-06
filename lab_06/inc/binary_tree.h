#ifndef BT_H
#define BT_H

typedef struct bt_node bt_node_t;
struct bt_node
{
  int value;
  bt_node_t *left;
  bt_node_t *right;
};

typedef struct bt bt_t;
struct bt
{
  bt_node_t *root;
};

#endif
