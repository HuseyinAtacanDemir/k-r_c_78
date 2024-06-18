#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "strutils.h"

struct nlist *hashtab[HASHSIZE];

int hash(char *s)
{
  int hashval;
  for (hashval = 0; *s != 0; hashval += *s++)
    ;
  return (hashval % HASHSIZE);
}

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
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL)
      return NULL;
    if ((np->name = str_save(name)) == NULL)
      return NULL;
    hashval = hash(np->name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free(np->def);
  }

  if ((np->def = str_save(def)) == NULL)
    return NULL;
  
  return np;
}
