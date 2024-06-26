#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

void error(char *, char *);

main(int argc, char **argv)
{
  char buf[BUFSIZE];
  int f, n;
  if (argc == 1)
    error("Usage: cat [file ...]", NULL);
  while (--argc > 0) {
    if ((f = open(*++argv, 0)) == -1)
      error("cat: can't open %s", *argv);
    while ((n = read(f, buf, BUFSIZE)) > 0)
      if (write(0, buf, n) != n)
        error("cat: write error", NULL);
    close(f);
  }
}

void error(char *s, char *p)
{
  printf(s, p);
  printf("\n");
  exit(1);
}
