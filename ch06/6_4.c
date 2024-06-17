#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "6_4_tree.h"
#include "6_5_2_getword.h"

#define DEF_BOUNDARY 7

void print_results(struct tnode *);
void print_sub_tree(struct tnode *);

main(int argc, char **argv)
{
  int boundary = argc > 1 ? atoi(*(argv+1)) : DEF_BOUNDARY;

  struct tnode *root;
  char word[MAXWORD];
  int t;
  int found = 0;

  root = NULL;
  while ((t = getword(word, MAXWORD)) != EOF)
    if (t == LETTER && strlen(word) >= boundary)
      root = insert(root, word, boundary, &found);
    found = 0;
  print_results(root);
}

void print_results(struct tnode *root)
{
  if (root == NULL)
    return;

  print_results(root->left);
  
  if (root->match)
    printf("%s\n", root->word);
  print_results(root->right);
}
