#ifndef tree_H
#define tree_H

typedef struct node node_t;
struct node
{
  int value;
  node_t *left;
  node_t *right;
  int height;
  // int count;
};

typedef struct tree tree_t;
struct tree
{
  node_t *root;
};

void free_node_t(node_t *root);
void free_tree_t_t(tree_t *tree);
node_t *find_node_t(node_t *root, int alpha, int *buf);
node_t *new_node_t(int alpha);
void add_node_t(node_t *root, int alpha);
void pri_node_t(node_t *root);
tree_t *new_tree_t(void);
void add_tree_t(tree_t *tree, int alpha);
void pri_tree_t(tree_t *tree);
node_t* del_node_t(node_t *root, node_t *current, int value, tree_t *tree_t);
void del_tree_t(tree_t *tree_t, int value);
// int get_height_node_t(node_t *root, int s);
// void fix_height_node_t(node_t *root, int s);
// void fix_height_tree_t(tree_t *tree_t);

int height(node_t* p);
int bfactor(node_t* p);
void fixheight(node_t* p);
node_t* rotateright(node_t* p);
node_t* rotateleft(node_t* q);
node_t* balance(node_t* p);
node_t* insert(node_t* p, int k);
node_t* findmin(node_t* p);
node_t* removemin(node_t* p);
node_t* delete(node_t* p, int k);

#endif
