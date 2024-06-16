#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "6_5_2_alloc.h"
#include "6_5_2_tree.h"
#include "6_5_2_getword.h"

#define COUNT 10
#define max(a, b) ((a) > (b) ? (a) : (b))

void treeprint_2d(struct tnode* root, int space)
{
  int i;
  if (root == NULL)
    return;
  space += COUNT;
  treeprint_2d(root->right, space);
  printf("\n");
  for (i = COUNT; i < space; i++)
    printf(" ");
  printf("|Word : %s\n", root->word);
  treeprint_2d(root->left, space);
}

void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

struct tnode * talloc()
{
  struct tnode *node = (struct tnode *) alloc_custom(sizeof(struct tnode));
  if (node == NULL) {
    printf("Memory cannot be allocated for tree node\n");
    exit(1);
  }
  return node;
}

struct tnode * new_node(char *word)
{
  struct tnode *node = talloc();
  node->word = strsave(word);
  node->count = 1;
  node->left = node->right = NULL;
  node->height = 1;
  return node;
}

struct tnode * tree(struct tnode *p, char *word)
{
  int cond;

  if (p == NULL) {
    p = new_node(word);
    return p;
  } 
  
  if ((cond = strcmp(word, p->word)) == 0) {
    p->count++;
    return p;
  } else if ( cond < 0 ) {
    p->left = tree(p->left, word);
  } else {
    p->right = tree(p->right, word);
  }

  int left_h = get_height(p->left);
  int right_h = get_height(p->right);
  p->height = left_h > right_h ? left_h + 1 : right_h + 1;

  int balance = get_balance(p);

  if (balance > 1 && strcmp(word, p->right->word) > 0)
    return rol(p);

  if (balance < -1 && strcmp(word, p->left->word) < 0)
    return ror(p);
  
  if (balance > 1 && strcmp(word, p->right->word) < 0) {
    p->right = ror(p->right);
    return rol(p);
  }

  if (balance < -1 && strcmp(word, p->left->word) > 0) {
    p->left = rol(p->left);
    return ror(p);
  }

  return p;
}

int get_height(struct tnode *node)
{
  if (node == NULL)
    return 0;
  return node->height;
}

// <-1 if right child taller >1 if left child taller
int get_balance(struct tnode *node)
{
  if (node == NULL)
    return 0;
  return get_height(node->right) - get_height(node->left);
}

struct tnode *ror(struct tnode *old_root_turned_r)
{
  if (old_root_turned_r == NULL || old_root_turned_r->left == NULL)
    return old_root_turned_r;

  struct tnode *new_root = old_root_turned_r->left;
  struct tnode *smaller_than_old_bigger_than_new = new_root->right;

  new_root->right = old_root_turned_r;
  old_root_turned_r->left = smaller_than_old_bigger_than_new;

  int old_root_turned_r_left_h = get_height(old_root_turned_r->left);
  int old_root_turned_r_right_h = get_height(old_root_turned_r->right);
  old_root_turned_r->height = max(old_root_turned_r_left_h, old_root_turned_r_right_h) + 1;

  int new_root_left_h = get_height(new_root->left); // this did not change
  int new_root_right_h = get_height(new_root->right); // this became old root, and the old value of this became the left of old root
  
  new_root->height = max(new_root_left_h, new_root_right_h) + 1;

  return new_root;
}

struct tnode *rol(struct tnode *old_root_turned_l)
{
  if (old_root_turned_l== NULL || old_root_turned_l->right == NULL)
    return old_root_turned_l;

  struct tnode *new_root = old_root_turned_l->right;
  struct tnode *bigger_than_old_smaller_than_new = new_root->left;

  new_root->left = old_root_turned_l;
  old_root_turned_l->right = bigger_than_old_smaller_than_new;

  int old_root_turned_l_left_h = get_height(old_root_turned_l->left);
  int old_root_turned_l_right_h = get_height(old_root_turned_l->right);
  old_root_turned_l->height = max(old_root_turned_l_left_h, old_root_turned_l_right_h) + 1;

  int new_root_right_h = get_height(new_root->right); //this did not change
  int new_root_left_h = get_height(new_root->left); // this became olf root, and the old value of this became the right of old root
  new_root->height = max(new_root_left_h, new_root_right_h) + 1;

  return new_root;
}
