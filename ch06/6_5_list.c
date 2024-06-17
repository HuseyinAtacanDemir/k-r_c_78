#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "6_5_list.h"
#include "6_5_2_alloc.h"

struct lnode * lalloc()
{
  struct lnode *node = (struct lnode *) alloc_custom(sizeof(struct lnode));
  if (node == NULL) {
    printf("Memory cannot be allocated for the list node\n");
    exit(1);
  }
  return node;
}

struct lnode * new_lnode(int line)
{
  struct lnode *node = lalloc();
  node->line_num = line;
  node->next = NULL;
  return node;
}

struct lnode * insert_lnode(struct lnode *head, int line)
{
  if (head == NULL) {
    return new_lnode(line);    
  }

  struct lnode *cur_tail, *tmp;
  
  tmp = head;
  while(tmp != NULL) {
    if (tmp->line_num == line)
      return head;
    cur_tail = tmp;
    tmp = tmp->next;
  }
  
  cur_tail->next = new_lnode(line);

  return head;
}
