#include <stdio.h>
#include <string.h>
void itoa(int n, char *s, int min);
void reverse(char *s);
void pad(int n, char *s);
main()
{
  int n = 123456;
  int min = 10;
  char s[100];
  itoa(n, s, min);
  printf("\n%s\n", s);
}

void itoa(int n, char *s, int min) 
{
  int sign = n;
  int i = 0;
  do {
    s[i++] = n >= 0 ? (n % 10) + '0' : -(n % 10) + '0';
  } while ((n /= 10) != 0);
  if(sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
  if(strlen(s) < min)
    pad(min - strlen(s), s);
}

void reverse(char *s)
{
  int i,j;
  for (i = 0, j = strlen(s)-1; j>i; i++, j--){
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
}

void pad(int n, char *s)
{
  int i = strlen(s) + n;
  for (; i >= 0; i--){
    if (i - n >= 0)
      s[i] = s[i-n];
    else
      s[i] = ' ';
  }
}
