#include <stdio.h>
#include <string.h>

main(int argc, char *argv[])
{
  int i;
  
  while (--argc > 0)
    printf("%s%c", *++argv, (argc > 1) ? ' ' : '\n');
}
