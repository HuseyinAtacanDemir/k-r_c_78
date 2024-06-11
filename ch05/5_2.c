#include <stdio.h>

void strcat_ptr(char *s, char *t);

main()
{
  char s[20] = "";
  char *t = "Hello World!";
  strcat_ptr(s, t);

  printf("%s\n", s);

}

//assumes s is large anough
void strcat_ptr(char *s, char *t)
{
  while (*s)  /* find end of s */
    s++;
  while ((*s++ = *t++)) /* copy t */
    ;
}
