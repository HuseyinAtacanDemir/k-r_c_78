#include <stdio.h>

#define MAXLINELEN 1000
#define MAXLINECOUNT 1000


int get_line(char *s, int lim);
void copy(char *s1, char *s2);

main ()
{
  int len;
  int max;
  int count;
  char line[MAXLINELEN];
  char save[MAXLINECOUNT][MAXLINELEN];
  int len_of_saved[MAXLINELEN];
  max = 80;
  count = 0;
  while ((len = get_line(line, MAXLINELEN)) > 0)
    if (len > max) {
      copy(line, save[count]);
      len_of_saved[count] = len;
      ++count;
    }
  int i;
  for (i = 0; i < count; i++)
    printf("\nLen: %d, Line: %s", len_of_saved[i], save[i]);
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
