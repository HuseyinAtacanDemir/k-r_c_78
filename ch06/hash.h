#ifndef HASH_H
#define HASH_H

struct nlist {
  char *name;
  char *def;
  struct nlist *next;
};

int hash(char *);
struct nlist * lookup(char *s);
struct nlist * install(char *, char *);

#endif
