#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char *s, int lim);
int index_custom(char *s, char *t);

main(int argc, char *argv[]) /* find pattern from first argument */
{
  char line[MAXLINE], *s;
  long lineno = 0;
  int except = 0, number = 0;

  /*
    While arg count is greater than 0,
    pre increment argv and check if first args first char is a -
    if it is a '-' then the following chars are options
    once an arg with no - prefix is seen loop is exited
    and argv ptr points to the next arg, which is assumed to be the pattern
  */
  while (--argc > 0 && (*++argv)[0] == '-')
    for (s = argv[0]+1; *s != '\0'; s++)
      switch (*s) {
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      default:
        printf("find: illegal option %c\n", *s);
        argc = 0;
        break;
      }
  /*
    If there is not exactly one argument left after the while loop that detects the options
    is run, that means the user utilized the tool incorrectly, since we assume the last arg to be
    the pattern
  */
  if (argc != 1)
    printf("Usage: find -x -n pattern\n");
  else
    while (get_line(line, MAXLINE) > 0) {
      //saving cur line num in case number option was selected
      lineno++;
      if ((index_custom(line, *argv) >= 0) != except) {
        if (number)
          printf("%ld: ", lineno);
        printf("%s", line);
        }
    }
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
