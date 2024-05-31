#include <stdio.h>
#include <string.h>

void reverse(char *s);

main()
{
  char in[100];
  char c;
  int i = 0;
  while((c = getchar()) != EOF)
    in[i++] = c;
  in[i] = '\0';

  reverse(in);
  printf("\n%s\n", in);
  
}

void reverse(char *s)
{
  int c, i, j;

  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
