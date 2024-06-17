#ifndef LIST_H
#define LIST_H

struct lnode {
  int line_num;
  struct lnode *next;
};

struct lnode * new_lnode(int);
struct lnode * insert_lnode(struct lnode *, int);

#endif
