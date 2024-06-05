#include <stdio.h>
#include <math.h>
#define BUFSIZE 100
#define SIZE 10

int get_float(double *pn);
char getch();
void ungetch(char c);

static char buf[BUFSIZE];
static int bufp = 0;

main()
{
  double v, array[SIZE];
  int n;
  
  for (n = 0; n < SIZE && get_float(&v) != EOF; n++)
    printf("arr[%d]: %f\n", n, (array[n] = v));
}

int get_float(double *pn)
{
  int c, sign, decimal_count;

  while ((c = getch()) == ' ' || c == '\n' || c == '\t')
    ;
  
  sign = 1;
  if (c == '+' || c == '-') {
    sign = (c == '+') ? 1 : -1;
    c = getch();
  }

  decimal_count = -1;
  for (*pn = 0; (c >= '0' && c <= '9') | (c == '.' && decimal_count == -1); c = getch()) {
    if (c == '.')
      decimal_count = 0;
    else {
      *pn = 10 * *pn + c - '0';
      if (decimal_count != -1)
        decimal_count++;
    }
  }

  *pn *= pow(10, decimal_count > 0 ? -decimal_count : 0);
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
