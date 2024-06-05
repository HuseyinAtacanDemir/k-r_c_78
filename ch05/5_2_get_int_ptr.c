#include <stdio.h>
#define BUFSIZE 100
#define SIZE 10

int get_int(int *pn);
char getch();
void ungetch(char c);

static char buf[BUFSIZE];
static int bufp = 0;

main()
{
  int n, v, array[SIZE];
  
  for (n = 0; n < SIZE && get_int(&v) != EOF; n++)
    printf("arr[%d]: %d\n", n, (array[n] = v));
}

int get_int(int *pn)
{
  int c, sign;

  while ((c = getch()) == ' ' || c == '\n' || c == '\t')
    ;
  
  sign = 1;
  if (c == '+' || c == '-') {
    sign = (c == '+') ? 1 : -1;
    c = getch();
  }

  for (*pn = 0; c >= '0' && c <= '9'; c = getch())
    *pn = 10 * *pn + c - '0';
  *pn *= sign;

  if (c != EOF)
    ungetch(c);

  return c;
}

char getch()
{
  return ((bufp > 0) ? buf[--bufp] : getchar());
}

void ungetch(char c)
{
  if (bufp > BUFSIZE)
    printf("ungetch: too amny characters\n");
  else
    buf[bufp++] = c;
}
