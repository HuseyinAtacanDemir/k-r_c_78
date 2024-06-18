#ifndef HASH_H
#define HASH_H

#define HASHSIZE 100

struct nlist {
  char *name;
  char *def;
  struct nlist *next;
};

extern struct nlist *hashtab[HASHSIZE];

int hash(char *);
struct nlist * lookup(char *s);
struct nlist * install(char *, char *);

#endif
