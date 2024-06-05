#include <stdio.h>

#define strcpy(s, t) { \
  char *target = t; \
  char *source = s; \
  while ((*target++ = *source++)) \
    ; \
  }

main()
{
  char *s = "Copy Me";
  char t[50]; 

  printf("t before: %s\n", t);
  strcpy(s, t);
  printf("t after: %s\n", t);
  
}
