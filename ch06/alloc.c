#include <stdio.h>
#include "alloc.h"

char mem_buf[MAX_MEM];
char *mem_ptr = mem_buf;

char *alloc_custom(int size)
{
  if (mem_ptr + size < mem_buf + MAX_SIZE) {
    mem_ptr += size;
    return mem_ptr - size;
  } else {
    printf("Memory allocation failed: out of memory\n");
    return NULL;
  }
}

void free(char *mem_block)
{
  if (mem_block >= mem_buf && mem_block < mem_buf + MAX_MEM)
    mem_ptr = mem_block;
}
