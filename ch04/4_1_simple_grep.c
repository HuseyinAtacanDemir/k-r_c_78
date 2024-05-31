#include <stdio.h>
#define MAXLINE 1000

int get_line(char *s, int lim);
int index( char *s, char *t);

main()
{
  char line[MAXLINE];

  while (get_line(line, MAXLINE) > 0)
    if (index(line, "the") >= 0)
      printf("%s", line);
}

int get_line(char *s, int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

int index(char *s, char *t)
{
  int i, j, k;
  
  for (i = 0; s[i] != '\0'; i++) {
    for( j = i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++ )
      ;
    if ( t[k] == '\0')
      return i;
  }
  return -1;
}
