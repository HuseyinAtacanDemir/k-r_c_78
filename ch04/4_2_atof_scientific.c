#include <stdio.h>
#define MAXLINE 100

double pow_custom(int base, int exp);

int get_line(char *s, int lim);
double atof(char *s);

main()
{
  char line[MAXLINE];

  while (get_line(line, MAXLINE) > 0)
    printf("\t%.2f\n", atof(line)); 
}

get_line(char *s, int lim) /* get line into s, return length */
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return(i);
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
