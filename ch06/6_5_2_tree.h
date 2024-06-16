#ifndef TREE_H
#define TREE_H

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

void treeprint(struct tnode *);
struct tnode * tree(struct tnode *, char *);

#endif
