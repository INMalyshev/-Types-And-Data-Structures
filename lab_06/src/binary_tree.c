#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

void free_node_t(node_t *root)
{
  if (root->left) free_node_t(root->left);
  if (root->right) free_node_t(root->right);
  free(root);
}

node_t *find_node_t(node_t *root, int alpha, int *buf)
{
  if (!root)
  {
    return NULL;
  }

  if (alpha < root->value)
  {
    *buf += 1;
    return find_node_t(root->left, alpha, buf);
  }
  else if (alpha == root->value)
  {
    *buf += 1;
    return root;
  }
  else
  {
    return find_node_t(root->right, alpha, buf);
  }
}

node_t *new_node_t(int alpha)
{
  node_t *new = malloc(sizeof(node_t));
  new->value = alpha;
  new->left = NULL;
  new->right = NULL;
  new->height = 1;
  // new->count = 1;

  return new;
}

int height(node_t* p)
{
	return p?p->height:0;
}

int bfactor(node_t* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node_t* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node_t* rotateright(node_t* p) // правый поворот вокруг p
{
	node_t* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node_t* rotateleft(node_t* q) // левый поворот вокруг q
{
	node_t* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node_t* balance(node_t* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node_t* insert(node_t* p, int k, int mod) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new_node_t(k);
	if( k<p->value )
		p->left = insert(p->left,k,mod);
	else
		p->right = insert(p->right,k,mod);
  if ( mod )
	 return balance(p);
  return p;
}

node_t* findmin(node_t* p) // поиск узла с минимальным ключом в дереве p
{
	return p->left?findmin(p->left):p;
}

node_t* removemin(node_t* p, int mod) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left, mod);
  if (mod)
	 return balance(p);
  return p;
}

node_t* delete(node_t* p, int k, int mod) // удаление ключа k из дерева p
{
	if( !p )
  {
    return 0;
  }
	if( k < p->value )
		p->left = delete(p->left,k,mod);
	else if( k > p->value )
		p->right = delete(p->right,k,mod);
  else //  k == p->key
	{
		node_t* q = p->left;
		node_t* r = p->right;
		// delete p;
    free(p);
		if( !r ) return q;
		node_t* min = findmin(r);
		min->right = removemin(r,mod);
		min->left = q;
    if (mod)
		  return balance(min);
    return min;
	}
  if (mod)
    return balance(p);
  return p;
}

void pri_node_t(node_t *p, int val)
{
  for (int i = 0; i < val; i++) printf(">---");
  if (p) printf("> %d\n", p->value);
  else printf("> NULL\n");
  if (p)
  {
    pri_node_t(p->left, val+1);
    pri_node_t(p->right, val+1);
  }
}
