#include <stdio.h>
#define MAXLINE 100

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
  double val, power;  
  int i, sign;

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

  return(sign * val / power);
}
