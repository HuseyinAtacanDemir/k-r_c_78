#ifndef TREE_H
#define TREE_H

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
  int height;
};

void treeprint_2d(struct tnode *, int);
void treeprint(struct tnode *);
struct tnode * new_node(char *);
struct tnode * tree(struct tnode *, char *);
int get_height(struct tnode *);
int get_balance(struct tnode *);
struct tnode * ror(struct tnode *);
struct tnode * rol(struct tnode *);

#endif
