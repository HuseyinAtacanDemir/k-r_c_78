#include <stdio.h>

void expand(char *s, char *t);

main(){

  char s1[100];
  char s2[100];
  char c;
  int i = 0;
  while ((c = getchar()) != EOF)
    s1[i++] = c;
  s1[i] = '\0';

  expand(s1, s2);

  printf("\n%s\n%s\n", s1, s2);

}

void expand(char *s, char *t)
{
  int i, j;
  for(i = j = 0; s[i] != EOF; i++, j++) {
    switch(s[i]){
      case '\n':
        t[j++] = '\\';
        t[j] = 'n';
        break;
      case '\t':
        t[j++] = '\\';
        t[j] = 't';
        break;
      case '\b':
        t[j++] = '\\';
        t[j] = 'b';
        break;
      default:
        t[j] = s[i];
        break;
    }
  }
  t[++j] = '\0';
}
