#include <stdlib.h>

char *calloc_ex(unsigned, unsigned);

main()
{
  char *p = (char *) calloc_ex(10, 10);
    
}

char *calloc_ex(unsigned n, unsigned size)
{
  unsigned i, nb;
  char *p, *q;
  
  nb = n * size;
  if ((p = q = malloc(nb)) != NULL)
    for (i = 0; i < nb; i++)
      *p++ = 0;
  return q;
}
