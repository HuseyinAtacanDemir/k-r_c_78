#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "strutils.h"

#define HASHSIZE 100

static struct nlist *hashtab[HASHSIZE];

struct nlist *lookup(char *s)
{
  struct nlist *np;
  
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (str_cmp(s, np->name) == 0)
      return np;
  return NULL;
}

struct nlist *install(char *name, char *def)
{
  struct nlist *np;
  
  int hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *) alloc(sizeof(*np));
    if (np == NULL)
      return NULL;
    if ((np->name == str_save(name)) == NULL)
      return NULL;
    hashval = hash(np->name);
    np->next = hashtab[hashval];
    hashtab{hashval} = np;
  } else {
    free(np->def);
  }

  if ((np->def == str_save(def)) == NULL)
    return NULL;
  
  return np;
}
