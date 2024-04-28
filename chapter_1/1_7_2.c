#include<stdio.h>

char lower(char c);

main()
{
  char c;
  while ((c = getchar()) != EOF) 
    putchar(lower(c));
}

char lower(char c)
{
  if( c >= 'A' && c <= 'Z')
    return (c + ('a' - 'A'));
  return c;
}
