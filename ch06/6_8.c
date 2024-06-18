/*
  boundaries:
    2 contiguous words following a #define statement (could be same line, new line etc...)
  read word by word
    special case #define
      if you see a #define consider next two words specially
      first word will be the name
      second will be the def
    once lookup encounters a name
      replace the name in the output with the corresponding def
*/

#include <stdio.h>
#include <ctype.h>
#include "hash.h"
#include "strutils.h"

#define BUFSIZE 30

int is_valid_name_char(char c);
char getch();
void ungetch(char c);

static char buf[BUFSIZE];
static int bufp = 0;

main()
{
  char word[BUFSIZE], name[BUFSIZE];

  char c;
  char *w = word;
  int define_ack = 0;

  while ((c = getch()) != EOF) {
    if (!is_valid_name_char(c)) {
      *w = '\0';
      struct nlist *np = lookup(word);
      if (str_cmp(word, "#define") == 0) {
        define_ack++;
      } else if (str_len(word) && define_ack == 1) {
        str_cpy(name, word);
        define_ack++;
      } else if (str_len(word) && define_ack == 2) {
        install(name, word);
        define_ack = 0;
      } else {
        define_ack = 0;
      }

      printf("%s", (np != NULL) ? np->def : word);

      w = word;
      printf("%c", c);
    } else if (is_valid_name_char(c)) {
      *w++ = c;
    }
  }
}

int is_valid_name_char(char c) 
{
  if (c == '_' || c == '#' || isalnum(c))
    return 1;
  return 0;
}

char getch()
{
  return ((bufp>0) ? buf[--bufp] : getchar());
}

void ungetch(char c)
{
  if (bufp > BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

