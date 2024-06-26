#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 512
#define PMODE 0644 

void error(char *, char *);

main(int argc, char **argv)
{
  int f1, f2, n;
  char buf[BUFSIZE];
  
  if (argc != 3)
    error("Usage: cp from to", NULL);
  if ((f1 = open(argv[1], 0)) == -1)
    error("cp: can't open %s", argv[1]);
  if ((f2 = creat(argv[2], PMODE)) == -1)
    error("cp: can't create %s", argv[2]);

  while ((n = read(f1, buf, BUFSIZE)) > 0)
    if (write(f2, buf, n) != n)
      error("cp: write error", NULL);

  exit(0);
}

void error(char *s, char *p)
{
  printf(s, p);
  printf("\n");
  exit(1);
}
