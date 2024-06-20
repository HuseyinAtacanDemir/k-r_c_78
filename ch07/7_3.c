#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 500

char * f_gets(char *, int, FILE *);

int main(int argc, char **argv)
{
  register FILE *f1, *f2;

  char l1[MAX_LINE_LEN], l2[MAX_LINE_LEN], *c1, *c2;

  if (--argc != 2) {
    fprintf(stderr, "diff: only diffs two files\n");
    exit(1);
  } else {
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    
    if (f1 == NULL) {
      fprintf(stderr, "diff: can't open file %s\n", argv[1]);
      exit(1);
    } 
    if (f2 == NULL) {
      fprintf(stderr, "diff: can't open file %s\n", argv[2]);
      exit(1);
    }
    
    int line_num = 0;
    int ch_pos = 0;
    while (
      (c1 = f_gets(l1, MAX_LINE_LEN, f1)) != NULL && 
      (c2 = f_gets(l2, MAX_LINE_LEN, f2)) != NULL
    ) {
      while (*c1 != '\0' && *c1 == *c2) {
        c1++;
        c2++;
        ch_pos++;
      }
      if (*c1 == *c2) {
        ch_pos = 0;
      } else {
        fprintf(stdout, "Line: %d, Pos:%d\n%s%s", line_num, ch_pos, l1, l2);
        exit(0);
      }
      line_num++;
    }

    fclose(f1);
    fclose(f2);
    return 0;
  }
}

char * f_gets(char *s, int n, register FILE *iop)
{
  register int c;
  register char *cs;

  cs = s;
  while (--n > 0 && (c = getc(iop)) != EOF)
    if ((*cs++ = c) == '\n')
      break;
  *cs = '\0';
  return ((c == EOF && cs == s) ? NULL : s);
}
