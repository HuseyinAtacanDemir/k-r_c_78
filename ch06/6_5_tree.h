#ifndef TREE_H
#define TREE_H

struct tnode {
  char *word;
  struct lnode *lines;
  struct tnode *left;
  struct tnode *right;
  int height;
};

void treeprint_2d(struct tnode *, int);
void treeprint(struct tnode *);
struct tnode * new_node(char *, int);
struct tnode * insert(struct tnode *, char *, int);
int get_height(struct tnode *);
int get_balance(struct tnode *);
struct tnode * balance_tree(struct tnode *, char *);
struct tnode * ror(struct tnode *);
struct tnode * rol(struct tnode *);

#endif
