#include <stdio.h>
#include <stdlib.h>

#define   MAXLINE   100
#define   TABING    8
#define   TRUE      1
#define   FALSE     0

void settab(int argc, char *argv[], char *tab);
void entab(char *tab);
void detab(char *tab);
int tabpos(int pos, char *tab);

main(int argc, char *argv[])
{
  char tab[MAXLINE + 1];
    
  settab(argc, argv, tab);
  entab(tab);
  
  return 0;
}

void entab(char *tab)
{
  int c, pos;
  int nb = 0;
  int nt = 0;

  for (pos = 1; (c=getchar()) != EOF; pos++) {
    if (c == ' ') {
      if (tabpos(pos, tab) == FALSE)
        ++nb;
      else {
        nb = 0;
        ++nt;
      }
    } else {
      for ( ; nt > 0; nt--)
        putchar('\t');
      if (c == '\t')
        nb = 0;
      else
        for ( ; nb > 0; nb--)
          putchar(' ');
      putchar(c);
      if (c == '\n')
        pos = 0;
      else if (c == '\t')
        while (tabpos(pos, tab) == FALSE)
          ++pos;
    }
  }
}

void detab(char *tab)
{
  int c, pos = 1;

  while ((c = getchar()) != EOF)
    if (c == '\t') {
      do {
        putchar(' ');
      } while (tabpos(pos++, tab) == FALSE);
    } else if (c == '\n') {
      putchar(c);
      pos = 1;
    } else {
      putchar(c);
      ++pos;
    }
}

void settab (int argc, char *argv[], char *tab)
{
  int i, inc, pos;
  
  if (argc <= 1) {
    for (i = 1; i <= MAXLINE; i++) 
      tab[i] = i % TABING == 0 ? TRUE : FALSE;
  } else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
    pos = atoi(&(*++argv)[1]);
    inc = atoi(&(*++argv)[1]);
    for (i = 1; i <= MAXLINE; i++)
      if (i != pos)
        tab[i] = FALSE;
      else {
        tab[i] = TRUE;
        pos += inc;
      }
  } else {
    for (i = 1; i <= MAXLINE; i++)
      tab[i] = FALSE;
    while (--argc > 0) {
      pos = atoi(*++argv);
      if (pos > 0 && pos <= MAXLINE)
        tab[pos] = TRUE;
    }
  }
}

int tabpos (int pos, char *tab)
{
  if (pos > MAXLINE)
    return TRUE;
  else
    return tab[pos];
}
