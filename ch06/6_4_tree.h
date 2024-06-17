#ifndef TREE_H
#define TREE_H

struct tnode {
  char *word;
  int match;
  struct tnode *left;
  struct tnode *right;
  int height;
};

struct tnode * new_tnode(char *, int *);
struct tnode * insert(struct tnode *, char *, int, int *);
int get_height(struct tnode *);
int get_balance(struct tnode *);
struct tnode * balance_tree(struct tnode *, char *);
struct tnode * ror(struct tnode *);
struct tnode * rol(struct tnode *);

#endif
