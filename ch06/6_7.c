#include <stdio.h>
#include "hash.h"
#include "strutils.h"

main()
{
  
}


struct nlist *remove_name_def(char *s)
{
  int hashval = hash(s);

  struct nlist *head = hashtab[hashval];
  struct nlist *cur, *prev = NULL;

  for (cur = head; cur != NULL; prev = cur, cur = cur->next)
    if (str_cmp(cur->name, s) == 0) {
      if (prev)
        prev->next = cur->next;
      else
        hashtab[hashval] = cur->next;
    }
  return cur;
}
