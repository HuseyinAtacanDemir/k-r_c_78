#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 20
#define LETTER 'a'
#define DIGIT '0'
#define NKEYS (sizeof(keytab))/(sizeof(struct key))

struct key {
  char *keyword;
  int keycount;
};

static struct key keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "do", 0,
  "double", 0,
  "else", 0,
  "enum", 0,
  "extern", 0,
  "float", 0,
  "for", 0,
  "goto", 0,
  "if", 0,
  "int", 0,
  "long", 0,
  "register", 0,
  "return", 0,
  "short", 0,
  "signed", 0,
  "sizeof", 0,
  "static", 0,
  "struct", 0,
  "switch", 0,
  "typedef", 0,
  "union", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0
};

int binary(char *, struct key[], int);
int getword(char *, int);
//char type(char);
char getch();
void ungetch(char);

char buf[BUFSIZE];
int bufp = 0;

int type[256];

main()
{
  int n, t;
  char word[MAXWORD];

  for (n = 0; n < 256; n++) {
    if (n >= 0x41 && n <= 0x5A || n >= 0x61 && n <= 0x7A)
      type[n] = 'a';
    else if (n >= 0x30 && n <= 0x39)
      type[n] = '0';
    else
      type[n] = -1;
  }
  
  while ((t = getword(word, MAXWORD)) != EOF)
    if (t == LETTER)
      if ((n = binary(word, keytab, NKEYS)) >= 0)
        keytab[n].keycount++;

  for (n = 0; n < NKEYS; n++)
    if (keytab[n].keycount > 0)
      printf("%4d %s\n", keytab[n].keycount, keytab[n].keyword);
}

int binary(char *word, struct key tab[], int n)
{
  int low, mid, high, cond;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high)/2;
    if ((cond = strcmp(word, tab[mid].keyword)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int getword(char *w, int lim)
{
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

//char type(char c)
//{
//  if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
//    return LETTER;
//  else if (c >= '0' && c <= '9')
//    return DIGIT;
//  else
//    return c;
//}


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

