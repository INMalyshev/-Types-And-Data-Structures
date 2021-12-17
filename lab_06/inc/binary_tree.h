#ifndef tree_H
#define tree_H

typedef struct node node_t;
struct node
{
  int value;
  node_t *left;
  node_t *right;
  int height;
};


void free_node_t(node_t *root);
node_t *find_node_t(node_t *root, int alpha, int *buf);
node_t *new_node_t(int alpha);
void pri_node_t(node_t *p, int val);

int height(node_t* p);
int bfactor(node_t* p);
void fixheight(node_t* p);
node_t* rotateright(node_t* p);
node_t* rotateleft(node_t* q);
node_t* balance(node_t* p);
node_t* insert(node_t* p, int k, int mod);
node_t* findmin(node_t* p);
node_t* removemin(node_t* p, int mod);
node_t* delete(node_t* p, int k, int mod);

#endif
