#include <stdio.h>
#include <string.h>
#include "6_5_2_alloc.h"
#include "6_5_2_getword.h"

char buf[BUFSIZE];
int bufp = 0;
int type[256];
int initialized = 0;

int str_cmp(char *s, char *t, int *found, int *match, int boundary)
{
  int i;
 
  for (i = 0; *s == *t; i++, s++, t++)
    if (*s == '\0')
      return 0;
  if (i >= boundary) {
    *found = 1;
    *match = 1;
  }
    
  return (*s-*t);
}

int initialize_type_lookup()
{
  int n;
  if (!initialized) {
    for (n = 0; n < 256; n++) {
      if (n >= 0x41 && n <= 0x5A || n >= 0x61 && n <= 0x7A) {
        type[n] = LETTER;
      } else if (n >= 0x30 && n <= 0x39) {
        type[n] = DIGIT;
      } else {
        type[n] = -1;
      }
    }
  }
  return 1;
}

int getword_with_line(char *w, int *line, int lim)
{  
  initialized = initialize_type_lookup();
  int c, t;
  c = *w++ = getch();
  if (c == '"') {
    while ((c = getch()) != '"' && c != EOF) {
      if (c == '\n')
        (*line)++; //increment line count
    }
      
    if (c == EOF) {
      *(w-1) = '\0';
      return c;
    } else {
      *(w-1) = c;
    }
  }

  if(c == '\n')
    (*line)++;
    
  if (type[c] != LETTER) {
    *w = '\0';
    return c;
  }

  while (--lim > 0) {
    c = *w++ = getch();
    t = type[c];
    if (t != LETTER && t != DIGIT) {
      ungetch(c);
      break;
    }
  }
  *(w-1) = '\0';
  return LETTER;
}

int getword(char *w, int lim)
{
  initialized = initialize_type_lookup();
  int c, t;
  c = *w++ = getch();
  if (c == '"') {
    while ((c = getch()) != '"' && c != EOF)
      ;
    if (c == EOF) {
      *(w-1) = '\0';
      return c;
    } else {
      *(w-1) = c;
    }
  }
    
  if (type[c] != LETTER) {
    *w = '\0';
    return c;
  }

  while (--lim > 0) {
    c = *w++ = getch();
    t = type[c];
    if (t != LETTER && t != DIGIT) {
      ungetch(c);
      break;
    }
  }
  *(w-1) = '\0';
  return LETTER;
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

char *strsave(char * w)
{
  int len = strlen(w) + 1;
  char *copy = alloc_custom(len);
  if (copy == NULL) {
    printf("Mem alloc failed\n");
    return NULL;
  }
  strcpy(copy, w);
  return copy;
}

