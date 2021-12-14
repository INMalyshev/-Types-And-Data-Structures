#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

void free_node_t(node_t *root)
{
  if (root->left) free_node_t(root->left);
  if (root->right) free_node_t(root->right);
  free(root);
}

void free_tree_t(tree_t *tree)
{
  free_node_t(tree->root);
  free(tree);
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

void add_node_t(node_t *root, int alpha)
{
  if (alpha <= root->value)
  {
    if (!root->left)
    {
      root->left = new_node_t(alpha);
      return;
    }
    add_node_t(root->left, alpha);
  }
  // else if (alpha == root->value)
  // {
  //   root->count += 1;
  //   return;
  // }
  else
  {
    if (!root->right)
    {
      root->right = new_node_t(alpha);
      return;
    }
    add_node_t(root->right, alpha);
  }
}

void pri_node_t(node_t *root)
{
  if (!root) return;

  printf("<value: %d", root->value);
  // if (1 < root->count) printf(", amount: %d", root->count);
  printf(">");
  if (root->left) printf(" <lson: %d>", root->left->value);
  if (root->right) printf(" <rson: %d>", root->right->value);
  // printf(" <[DBG] h = %d>", root->height);
  printf("\n");

  pri_node_t(root->left);
  pri_node_t(root->right);
}

tree_t *new_tree_t(void)
{
  return calloc(1, sizeof(tree_t));
}

void add_tree_t(tree_t *tree, int alpha)
{
  if (!tree->root) tree->root = new_node_t(alpha);
  else add_node_t(tree->root, alpha);
}

void pri_tree_t(tree_t *tree)
{
  printf("Binary search tree prefix form:\n\n");

  if (!tree->root)
  {
    printf("No nodes in tree.\n");
    return;
  }

  pri_node_t(tree->root);
}

/* Возвращает указатель на "вырванный" из дерева элемент (без очистки) */
node_t* del_node_t(node_t *root, node_t *current, int value, tree_t *tree)
{
  if (!current)
  {
    return NULL;
  }

  else if (value < current->value)
  {
    return del_node_t(current, current->left, value, tree);
  }

  else if (value > current->value)
  {
    return del_node_t(current, current->right, value, tree);
  }

  else
  {
    if (!(current->left || current->right) && root) // Обработка листа
    {
      if (root)
      {
        if (current == root->left)
        {
          root->left = NULL;
          return current;
        }
        else
        {
          root->right = NULL;
          return current;
        }
      }
      else
      {
        tree->root = NULL;
        return NULL;
      }
    }

    else if (!(current->left && current->right) && (current->left || current->right)) // У узла есть всего один потомок
    {
      node_t *new_current = current->left;

      if (!new_current)
      {
        new_current = current->right;
      }

      if (root)
      {
        if (current == root->left)
        {
          root->left = new_current;
          return current;
        }
        else
        {
          root->right = new_current;
          return current;
        }
      }
      else
      {
        tree->root = new_current;
        return current;
      }
    }

    else // У узла есть два потомка
    {
      node_t *new_current = current->left;
      node_t *root_for_new_current = current;

      if (new_current->right)
      {
        new_current = new_current->right;
        root_for_new_current = root_for_new_current->left;
      }

      while (new_current->right)
      {
        new_current = new_current->right;
        root_for_new_current = root_for_new_current->right;
      }

      if (new_current == root_for_new_current->left)
      {
        root_for_new_current->left = NULL;
      }
      else
      {
        root_for_new_current->right = NULL;
      }

      new_current->left = current->left;
      new_current->right = current->right;

      if (root)
      {
        if (current == root->left)
        {
          root->left = new_current;
          return current;
        }
        else
        {
          root->right = new_current;
          return current;
        }
      }
      else
      {
        tree->root = new_current;
        return current;
      }
    }
  }
}

node_t *del(node_t *p, int k)
{
	if( !p )
  {
    // printf("Noting found.\n");
    return 0;
  }
	if( k < p->value )
		p->left = del(p->left,k);
	else if( k > p->value )
		p->right = del(p->right,k);
  else //  k == p->key
	{
		node_t* q = p->left;
		node_t* r = p->right;
		// delete p;
    free(p);
		if( !r ) return q;
		node_t* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return min;
	}
  return p;
}

void del_tree_t(tree_t *tree, int value)
{
  // node_t *removed_node = del_node_t(NULL, tree->root, value, tree);
  tree->root = del(tree->root, value);
  // if (!removed_node)
  // {
  //   printf("Nothing found.\n");
  //   return;
  // }

  // free(removed_node);

  // printf("Success\n");
}

// int get_height_node_t(node_t *root, int s)
// {
//   if (!root)
//     return s;
//
//   s += 1;
//
//   int h1 = get_height_node_t(root->left, s);
//   int h2 = get_height_node_t(root->right, s);
//
//   return (h1 > h2) ? h1 : h2;
// }
//
// void fix_height_node_t(node_t *root, int s)
// {
//   if (!root) return;
//
//   root->height = s;
//
//   fix_height_node_t(root->left, s-1);
//   fix_height_node_t(root->right, s-1);
// }
//
// void fix_height_tree_t(tree_t *tree)
// {
//   int h = get_height_node_t(tree->root, -1);
//   fix_height_node_t(tree->root, h);
// }

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

node_t* insert(node_t* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new_node_t(k);
	if( k<p->value )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

node_t* findmin(node_t* p) // поиск узла с минимальным ключом в дереве p
{
	return p->left?findmin(p->left):p;
}

node_t* removemin(node_t* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node_t* delete(node_t* p, int k) // удаление ключа k из дерева p
{
	if( !p )
  {
    // printf("Noting found.\n");
    return 0;
  }
	if( k < p->value )
		p->left = delete(p->left,k);
	else if( k > p->value )
		p->right = delete(p->right,k);
  else //  k == p->key
	{
		node_t* q = p->left;
		node_t* r = p->right;
		// delete p;
    free(p);
		if( !r ) return q;
		node_t* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
  return balance(p);
}
