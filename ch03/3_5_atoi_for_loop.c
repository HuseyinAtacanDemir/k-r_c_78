#include <stdio.h>

int atoi(char *s);

main(){
  char in[100];
  char c;
  int i = 0;
  while((c = getchar()) != EOF)
    in[i++] = c;
  in[i] = '\0';
  
  printf("\nNumber: %d\n", atoi(in));
}

int atoi(char *s)
{
  int i, n, sign;

  for(i=0; s[i]==' ' || s[i]=='\n' || s[i]=='\t'; i++)
    ; /* skip whitespaces */
  sign = 1;
  if (s[i] == '+' || s[i] == '-') /* sign if provided, else assume positive */
    sign = (s[i++] == '+') ? 1 : -1;
  for (n = 0; s[i] >= '0' && s[i] <= '9'; i++)
    n = 10 * n + (s[i] - '0');

  return (sign * n);  
}
