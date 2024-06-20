#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char *s, int lim);
int index_custom(char *s, char *t);

main(int argc, char *argv[]) /* find pattern from first argument */
{
  char line[MAXLINE], *s;
  long lineno = 0;
  long char_pos = 0;
  int except = 0, number = 0, multi_file = 0;

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

  if (argc > 1) {
    char *pattern = *argv++;
    if (argc > 2) {
      multi_file = 1;
    }
    while (--argc > 0) {
      FILE *fp = fopen(*argv, "r");
      if (fp == NULL) {
        fprintf(stderr, "grep: can't open %s\n", *argv);
        exit(1);
      }
      char *c;
      lineno = 0;
      while (fp != NULL && (c = fgets(line, MAXLINE, fp)) != NULL) {
        if (((char_pos = index_custom(line, pattern)) >= 0) != except) {
          if (number) {
            if (multi_file)
              printf("%s ", *argv);
            printf("%ld:%ld ", lineno, char_pos);
          }
          printf("%s", line);
        }
        lineno++;
      }
      fclose(fp);
      argv++;
    }
  } else if (argc == 1) {
    while (get_line(line, MAXLINE) > 0) {
      //saving cur line num in case number option was selected
      lineno++;
      if ((index_custom(line, *argv) >= 0) != except) {
        if (number)
          printf("%ld: ", lineno);
        printf("%s", line);
      }
    }
  } else {
    printf("Usage: find -x -n pattern\n");
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
