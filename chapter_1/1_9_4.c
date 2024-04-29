#include <stdio.h>

#define MAXLINELEN 1000

int get_line(char *s, int lim);
void copy(char *s1, char *s2);
void reverse(char *s);
int str_len(char *s);

main ()
{
  int len;
  int count;
  char line[MAXLINELEN];
  char save[MAXLINELEN];
  
  while ((len = get_line(line, MAXLINELEN)) > 0 ) {
      copy(line, save);
      reverse(save);
      printf("Reversed: %s\n", save);
  }
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

  if (i <= lim -1)
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

void reverse(char *s)
{
  int len = str_len(s);
  if (len == 0 || len == 1)
    return;
  int i, j;
  
  for (i = 0, j = len - 1; i < j; ++i, --j) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}

int str_len(char *s)
{
  int i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}
