#include <stdio.h>

#define MAXLINE 1000

char line[MAXLINE];
char save[MAXLINE];
int max;

int get_line();
void copy();

main()
{
  int len;
  extern int max;
  extern char save[];
  max = 0;
  while ((len = get_line()) > 0)
    if (len > max) {
      max = len;
      copy();
    }
  if (max > 0)
    printf("%s", save);
}

int get_line()
{
  int c, i;
  extern char line[];

  i = 0;
  c = EOF;

  while (i < MAXLINE-1 && (c = getchar()) != EOF && c != '\n')
    line[i++] = c;

  if (c == '\n')
    line[i++] = c;
    
  line[i] = '\0';
  return i;
}

void copy() 
{
  int i;
  extern char line[], save[];

  i = 0;
  while ((save[i] = line[i]) != '\0')
    ++i;
}

