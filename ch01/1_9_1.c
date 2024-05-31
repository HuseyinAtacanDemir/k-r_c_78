#include <stdio.h>

#define MAXLINE 1000

int get_line(char *s, int lim);
void copy(char *s1, char *s2);

main ()
{
  int len;
  int max;
  char line[MAXLINE];
  char save[MAXLINE];

  max = 0;
  while ((len = get_line(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copy(line, save);
    }
  if (max > 0)
    printf("Len: %d, Line: %s", max, save);
} 

int get_line(char *s, int lim)
{
  int c, i, nl;
  nl = 0;
  i = 0;
  while ((c=getchar()) != EOF) {
    if (c == '\n') {
      nl = 1;
      break;
    }
    if ( i < lim - 2 )
      s[i] = c;    
    ++i;
  }

  if (nl == 1) {
    if (i <= lim - 2)
      s[i] = '\n';
    else
      s[lim-2] = '\n';
    ++i;
  }

  if ( i <= lim -1)
    s[i] = '\0';
  else
    s[lim - 1] = '\0';
  
  return i;
}

void copy(char *s1, char *s2)
{
  int i;

  i = 0;
  while ((s2[i] = s1[i]) != '\0')
    ++i;
}
