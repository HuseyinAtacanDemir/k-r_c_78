#include <stdio.h>
#include "6_5_2_tree.h"
#include "6_5_2_getword.h"
#include "6_5_2_alloc.h"

/*
  Suppose we want to handle the more general problem of counting the occurrences of all the words in some input.
  Since the list of words isn't knwon in advance, we can't conveniently sort it and use a binary search.
  Yet we can't do a linear search for each word as it arrives, to see if it's already been seen; the program 
  would take forever [more precisely, its expected running time would grow quadratically with the number of input words] 
  
  One solution is to keep the set of words seen so far sorted at all times, by placing each word into its proper position
  in the order as it arrives. This should not be done by shifting words in a linear array though, that also takes too long.
  Instead we will use a data structure called a binary tree.
*/


int get_tree_size(struct tnode *);
void init_tree_arr(struct tnode **, struct tnode *);
void sort_nodes(struct tnode **, int, int);
void print_nodes(struct tnode **, int);

static int tree_arr_idx = 0;

main()
{
  struct tnode *root;
  char word[MAXWORD];
  int t;

  root = NULL;
  while ((t = getword(word, MAXWORD)) != EOF)
    if (t == LETTER)
      root = insert(root, word);

  int tree_size = get_tree_size(root);
  
  struct tnode **nodes = (struct tnode **) alloc_custom((tree_size * sizeof(struct tnode *)));

  init_tree_arr(nodes, root);

  sort_nodes(nodes, tree_size, -1);
  print_nodes(nodes, tree_size);
}

int get_tree_size(struct tnode *root) {
  if (root == NULL)
    return 0;

  if (root->left == NULL && root->right == NULL)
    return 1;

  int left_size = get_tree_size(root->left);
  int right_size = get_tree_size(root->right);

  return left_size + right_size + 1;
}

void init_tree_arr(struct tnode **nodes, struct tnode *root)
{
  if(root == NULL)
    return;

  init_tree_arr(nodes, root->left);
  nodes[tree_arr_idx++] = root;
  init_tree_arr(nodes, root->right);
}

void sort_nodes(struct tnode **nodes, int size, int sort_direction)
{
  int i, j;
  for (i = 0; i < size-1; i++) {
    for (j = i+1; j < size; j++) {
      struct tnode *node1 = nodes[i];
      struct tnode *node2 = nodes[j];
      if (sort_direction == 1 && node1->count > node2->count) {
        nodes[j] = node1;
        nodes[i] = node2;
      } else if (sort_direction == -1 && node1->count < node2->count) {
        nodes[j] = node1;
        nodes[i] = node2;
      }
    }
  }
}

void print_nodes(struct tnode **nodes, int size)
{
  int i;
  for (i = 0; i < size; i++ )
    printf("%4d %s\n", (nodes[i])->count, (nodes[i])->word);
}
