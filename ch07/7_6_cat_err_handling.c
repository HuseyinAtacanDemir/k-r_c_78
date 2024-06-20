#include <stdio.h>
#include <stdlib.h>

void file_copy(FILE *);

main (int argc, char **argv)
{
  FILE *fp;

  if (argc == 1)
    file_copy(stdin);
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "cat: can't open %s\n", *argv);
        exit(1);
      } else {
        file_copy(fp);
        fclose(fp);
      }
}

void file_copy(FILE *fp)
{
  int c;
  while ((c = getc(fp)) != EOF)
    putc(c, stdout);
}
