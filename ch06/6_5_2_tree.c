#include <stdio.h>
#include <string.h>
#include "6_5_2_alloc.h"
#include "6_5_2_tree.h"
#include "6_5_2_getword.h"

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
  return ((struct tnode *) alloc_custom(sizeof(struct tnode)));
}

struct tnode * tree(struct tnode * p, char * word)
{
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strsave(word);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(word, p->word)) == 0) {
    p->count++;
  } else if ( cond < 0 ) {
    p->left = tree(p->left, word);
  } else {
    p->right = tree(p->right, word);
  }
  return p;
}

