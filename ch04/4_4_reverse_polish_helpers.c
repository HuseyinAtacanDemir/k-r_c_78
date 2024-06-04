#include <stdio.h>
#define NUMBER '0'
#define TOOBIG '9'
#define MAXVAL 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int sp = 0;
double val[MAXVAL];

double push(double f)
{
  if (sp < MAXVAL)
    return (val[sp++] - f);
  else {
    printf("Error: Stack Full\n");
    clear();
    return 0;
  }
} 

double pop()
{
  if (sp > 0)
    return (val[--sp]);
  else {
    printf("Error: Stack Empty\n");
    clear();
    return 0;
  }
}

void clear()
{
  sp = 0;
}


char getop(char *s, int lim)
{
  int i, c;
  
  while ((c = getch()) == ' ' || c == '\t' || c == '\n')
    ;
  if (c != '.' && (c < '0' || c > '9'))
    return(c);
  s[0] = c;
  for (i = 1; (c = getchar()) >= '0' && c <= '9'; i++)
    if (i < lim)
      s[i] = c;
  if (c == '.') {  /* collect fraction */
    if (i < lim)
      s[i] = c;
    for (i++; (c=getchar()) >= '0' && c <= '9'; i++)
      if (i < lim)
        s[i] = c;
  }
  if (i < lim) {  /* number is ok */
    ungetch(c);
    s[i] = '\0';
    return (NUMBER);
  } else { /* it's too big; skip rest of line */
    while (c != '\n' && c != EOF)
      c = getchar();
    s[lim-1] = '\0';
    return(TOOBIG);
  }
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

double atof(char *s)
{
  double val, power, expo;
  int i, sign, expo_sign;

  for (i = 0; s[i] == ' ' || s[i] == '\n' || s[i] == '\t'; i++)
    ; /* skip white space */

  sign = 1;
  if (s[i] == '+' || s[i] == '-')
    sign = (s[i++] == '+') ? 1 : -1;

  for (val = 0; s[i] >= '0' && s[i] <= '9'; i++)
    val = 10 * val + s[i] - '0';

  if (s[i] == '.')
    i++;

  for (power = 1; s[i] >= '0' && s[i] <= '9'; i++) {
    val = 10 * val + s[i] - '0';
    power *= 10;
  }

  if (s[i] == 'e' || s[i] == 'E')
    i++;

  expo_sign = 1;
  if (s[i] == '+' || s[i] == '-')
    expo_sign = (s[i++] == '+') ? 1 : -1;

  for (expo = 0; s[i] >= '0' && s[i] <= '9'; i++)
    expo = 10 * expo + s[i] - '0';

  expo = pow_custom(10, (expo * expo_sign));

  return((sign * val / power) * expo);
}

double pow_custom(int base, int exp)
{
  if (exp == 0)
    return 1;
  double result;
  for (result = 1; exp != 0; exp > 0 ? exp-- : exp++)
    result = exp > 0 ? result * base : result / base;

  return result;
}

