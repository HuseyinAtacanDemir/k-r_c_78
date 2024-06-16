#include <stdio.h>
#include "6_5_2_alloc.h"

char mem_buf[MAX_MEM];
char *mem_ptr = mem_buf;

char * alloc_custom(int n)
{
  if (mem_ptr + n <= mem_buf + MAX_MEM) {
    mem_ptr += n;
    return (mem_ptr - n);
  } else 
    return NULL;
}

void free_custom(char *p)
{
  if (p >= mem_buf && p < mem_buf + MAX_MEM)
    mem_ptr = p;
}
