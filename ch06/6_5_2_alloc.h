#ifndef ALLOC_H
#define ALLOC_H

#define MAX_MEM 10000

extern char mem_buf[MAX_MEM];
extern char *mem_ptr;

char * alloc_custom(int);
void free_custom(char *);

#endif
