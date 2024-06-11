#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char *s, int lim);
int index_custom(char *s, char *t);

main(int argc, char *argv[]) /* find pattern from first argument */
{
  char line[MAXLINE];

  if (argc != 2)
    printf("Usage: find pattern\n");
  else
    while (get_line(line, MAXLINE) > 0)
      if (index_custom(line, argv[1]) >= 0)
        printf("%s", line);
}

int get_line(char *s, int lim) /* get line into s, return length */
{
    char *p = s;
    int c;

    for ( ; lim > 0 && (c=getchar())!=EOF && c!='\n'; lim--)
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return(s - p);
}


int index_custom(char *s, char *t) /* return index of t in s, -1 if none */
{
  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
      ;
    if (t[k] == '\0')
      return(i);
  }
  return (-1) ;
}
