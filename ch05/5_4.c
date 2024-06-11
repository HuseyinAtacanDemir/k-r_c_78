#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int get_line_1_ptr(char *s, int lim);
int atoi_ptr(char *s);
void itoa(int n , char *s);
double atof(char *s);
void reverse(char *s);
int str_len(char *s);
main()
{

}
/*
  returns the length of the line

  int c is for holding the char that is read
  char *t is a pointer set to char *s
  char *s initially points to the starting address to the block allocated for the line to be read
  int lim is the max len of the line to be read

  in a while loop, we decrement the lim until 1 (leaving space for \0),
  and get a new char using getchar() at each iteration,
  until we come across a '\n' char.
  In the loop we set the current char c to the value of the current address of s
  then increment s: *s++ = c
  
  after the loop we check if the last char was a \n,
  if yes we add that to s and increment s
  
  we subtract t from s, since s was incremented for all chars, and t was the original address of t
  we end up getting the length of the str
*/
int get_line_1_ptr(char *s, int lim)
{
  int c;
  char *t = s;

  while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    *s++ = c;
  if (c == '\n')
    *s++ = c;
  *s = '\0';
  return s - t;
}

/*
  we skip space chars, incrementing s
  we check the sign
  we skip the sign char if exists
  for all digit chars, we multiply the collector n by ten, then add the digit itself
  we calculate the digit by subtracting '0' ascii value from the ascii value we get for the cur char in *s
  return by multiplying sign and collector
*/
int atoi_ptr(char *s)
{
  int n, sign;

  for ( ; isspace(*s); s++)
    ;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  for (n = 0; isdigit(*s); s++)
    n = 10 * n + *s - '0';

  return sign * n;
}

void itoa(int n, char *s)
{
  int sign;
  char *t = s;
  
  if ((sign = n) < 0)
    n = -n;

  do {
    *s++ =  % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    *s++ = '-';
  reverse(t);
}

double atof(char *s)
{
  double val, power;
  int sign;

  for ( ; isspace(*s); s++)
    ;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+')
    s++;
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10.0;
  }
  return sign * val / power;
}

/*
  two pointers s and t, increment form start decrement from end, swap, end when two cross one another.
*/
void reverse(char *s)
{
  char c;
  char *t;
  for (t = (str_len(s)-1); s < t; s++, t--) {
    c = *s;
    *s = *t;
    *t = c;
  }
}
// record the starting address to t, increment s until null value, return s-t
int str_len(char *s)
{
  char *t = s;

  while (*s++)
    ;
  return (s-t);
}

int str_idx(char *s, char *t)
{
  char *b = s;
  char *p, *r;

  while(*s++) {
    for (p = s, r = t; *r && *p == *r; p++, r++)
      ;
    if (r > t && *r)
      return s - b;
  }
  return -1;
}
