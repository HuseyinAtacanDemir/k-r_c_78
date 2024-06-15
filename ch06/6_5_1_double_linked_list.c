#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

struct lnode {
  char *text;
  struct lnode *prev;
  struct lnode *next;
};

int main()
{
  struct lnode *head = NULL;
  struct lnode *tail = NULL;
  struct lnode *cur;

  char line[MAXLINE];

  while (fgets(line, MAXLINE, stdin) != NULL) {
    char *save = (char *) malloc(strlen(line)+1);
    strcpy(save, line);
    
    struct lnode *new = (struct lnode *) malloc(sizeof(struct lnode));

    new->text = save;
    new->next = NULL;
    new->prev = tail;

    if (head == NULL) head = new;

    if (tail != NULL) tail->next = new;
    tail = new;
  }
  //reverse order printing
  for (cur = tail; cur != NULL; cur = cur->prev)
    printf("%s", cur->text);

  return 0;
}
