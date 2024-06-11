#include <stdio.h>
#include <string.h>

main(int argc, char *argv[])
{
  int i;
  
  while (--argc > 0)
    printf((argc > 1) ? "%s " : "%s\n", *++argv);
}
