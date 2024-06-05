#include <stdio.h>


/*
  char *p;
  *p++ returns the char p points to, then increments p
  *p-- returns the char p points to, then decrements p

  *++p increments p, then returns the char p then points to
  *--p decrements p, then returns the char p then points to
*/

main()
{
  char *message;

  message = "I am a string constant";

  printf("I am another string constant");
}


void str_cpy_array(char s[], char t[])
{
  int i;
  i = 0;
  while ((s[i] = t[i]) != '\0')
    i++;
}

void str_cpy_ptr_1(char *s, char *t)
{
  while((*s = *t) != '\0') {
    s++;
    t++;
  }
}

//postfix ++ does not change t until the char has been fetched
//in the same way, the char is stored into the old s position before s is incremented
//this char is also the value that is compared against \0
void str_cpy_ptr_2(char *s, char *t)
{
  while ((*s++ = *t++) != '\0')
    ;
}

//check against \0 is redundant since \0 itself is a false value within the while control
void str_cpy_ptr_3(char *s, char *t)
{
  while ((*s++ = *t++))
    ;
}


// return <0 if s<t, 0 if s==t, >0 if s>t
int str_cmp_arr(char s[], char t[])
{
  int i;

  i = 0;
  while (s[i] == t[i])
    if (s[i++] == '\0')
      return 0;
  return (s[i] - t[i]);
}

int str_cmp_ptr(char *s, char *t)
{
  for ( ; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return (*s - *t);
}

