#include <stdio.h>

main()
{
  long nc;
  
  nc = 0;
  while (getchar() != EOF) /* ^D is EOF in unix systems */
    ++nc;
  printf("\nCharacter count: %ld\n", nc);

}
