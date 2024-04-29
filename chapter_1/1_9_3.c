#include <stdio.h>

#define MAXLINELEN 1000
#define MAXLINECOUNT 1000


int get_line(char *s, int lim);
void copy(char *s1, char *s2);
void trim_end(char *s);

main ()
{
  int len;
  int count;
  char line[MAXLINELEN];
  char save[MAXLINECOUNT][MAXLINELEN];
  
  for (count = 0; (len = get_line(line, MAXLINELEN)) > 0 && count < MAXLINECOUNT; ++count) {
    if (len == 1 && line[0] == '\n')
      count--;
    else {
      trim_end(line);
      copy(line, save[count]);
    }
  }
  int i;
  for (i = 0; i < count; i++)
    printf("%s", save[i]);
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

void trim_end(char *s) 
{
  int i = 0;
  int nl = 0;
  while (s[i] != '\0')
    ++i;
  if (i == 0)
    return;
  --i;
  if (s[i] == '\n') {
    --i;
    nl = 1;
  }
  if (i == 0)
    return;
  while ((s[i] == '\t' || s[i] == ' ') && i >= 0)
    --i;
  if (nl == 1) {
    s[i+1] = '\n';
    s[i+2] = '\0';
  } else
    s[i+1] = '\0';
}
