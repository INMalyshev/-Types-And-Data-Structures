#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

void free_bt_node_t(bt_node_t *root)
{
  if (root->left) free_bt_node_t(root->left);
  if (root->right) free_bt_node_t(root->right);
  free(root);
}

void free_bt_t(bt_t *bt)
{
  free_bt_node_t(bt->root);
  free(bt);
}

bt_node_t *find_bt_node_t(bt_node_t *root, int alpha, int *buf)
{
  if (!root)
  {
    return NULL;
  }

  if (alpha < root->value)
  {
    *buf += 1;
    return find_bt_node_t(root->left, alpha, buf);
  }
  else if (alpha == root->value)
  {
    *buf += 1;
    return root;
  }
  else
  {
    return find_bt_node_t(root->right, alpha, buf);
  }
}

// bt_node_t *find_root_bt_node_t(bt_node_t *root, int alpha)
// {
//   if (!root)
//   {
//     return NULL;
//   }
//
//   if (alpha < root->value)
//   {
//     return find_root_bt_node_t(root->left, alpha);
//   }
//   else if ((root->left && alpha == root->left->value) || (root->right &&  alpha == root->right->value))
//   {
//     return root;
//   }
//   else
//   {
//     return find_root_bt_node_t(root->right, alpha);
//   }
// }

bt_node_t *new_bt_node_t(int alpha)
{
  bt_node_t *new = malloc(sizeof(bt_node_t));
  new->value = alpha;
  new->left = NULL;
  new->right = NULL;
  new->count = 1;

  return new;
}

void add_bt_node_t(bt_node_t *root, int alpha)
{
  if (alpha < root->value)
  {
    if (!root->left)
    {
      root->left = new_bt_node_t(alpha);
      return;
    }
    add_bt_node_t(root->left, alpha);
  }
  else if (alpha == root->value)
  {
    root->count += 1;
    return;
  }
  else
  {
    if (!root->right)
    {
      root->right = new_bt_node_t(alpha);
      return;
    }
    add_bt_node_t(root->right, alpha);
  }
}

void pri_bt_node_t(bt_node_t *root)
{
  if (!root) return;

  printf("<value: %d", root->value);
  if (1 < root->count) printf(", amount: %d", root->count);
  printf(">");
  if (root->left) printf(" <son: %d>", root->left->value);
  if (root->right) printf(" <son: %d>", root->right->value);
  printf("\n");

  pri_bt_node_t(root->left);
  pri_bt_node_t(root->right);
}

bt_t *new_bt_t(void)
{
  return calloc(1, sizeof(bt_t));
}

void add_bt_t(bt_t *bt, int alpha)
{
  if (!bt->root) bt->root = new_bt_node_t(alpha);
  else add_bt_node_t(bt->root, alpha);
}

void pri_bt_t(bt_t *bt)
{
  printf("Binary search tree prefix form:\n\n");

  if (!bt->root)
  {
    printf("No nodes in tree.\n");
    return;
  }

  pri_bt_node_t(bt->root);
}

// void del_pb_node_t(bt_node_t **p, int x)
// {
//   if (NULL == *p)
//   {
//     printf("Nothing found.\n");
//     return;
//   }
//
//   else if ((*p)->value < x)
//   {
//     del_pb_node_t(&((*p)->left), x);
//   }
//
//   else if ((*p)->value > x)
//   {
//     del_pb_node_t(&((*p)->right), x);
//   }
//
//   else
//   {
//     if (!(*p)->left && !(*p)->right)
//     {
//       free(*p);
//       *p = NULL;
//     }
//
//     else if ((*p)->left && !(*p)->right)
//     {
//       void *tofree = *p;
//       *p = (*p)->left;
//       free(tofree);
//     }
//
//     else if (!(*p)->left && (*p)->right)
//     {
//       void *tofree = *p;
//       *p = (*p)->right;
//       free(tofree);
//     }
//
//     else
//     {
//       printf("todo");
//     }
//   }
// }

/* Возвращает указатель на "вырванный" из дерева элемент (без очистки) */
bt_node_t* del_pb_node_t(bt_node_t *root, bt_node_t *current, int value, bt_t *tree)
{
  if (!current)
  {
    return NULL;
  }

  else if (value < current->value)
  {
    return del_pb_node_t(current, current->left, value, tree);
  }

  else if (value > current->value)
  {
    return del_pb_node_t(current, current->right, value, tree);
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
        return current;
      }
    }

    else if (!(current->left && current->right) && (current->left || current->right)) // У узла есть всего один потомок
    {
      bt_node_t *new_current = current->left;

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
      bt_node_t *new_current = current->left;
      bt_node_t *root_for_new_current = current;

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

void del_bt_t(bt_t *tree, int value)
{
  bt_node_t *removed_node = del_pb_node_t(NULL, tree->root, value, tree);
  if (!removed_node)
  {
    printf("Nothing found.\n");
    return;
  }

  free(removed_node);

  printf("Success\n");
}
