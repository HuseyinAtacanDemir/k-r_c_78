#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 512

int get(int, long, char *, int);

main(int argc, char **argv)
{
  char buf[BUFSIZE];
  long pos = 100L;
  int n = 100;
  int fd;

  if (argc != 2)
    exit(1);

  if ((fd = open(*++argv, 0)) == -1)
    exit(1);
  
  if ((get(fd, pos, buf, n)) > 0)
    if ((write(0, buf, n)) != n)
      exit(1);

  close(fd);
  exit(0);
}

int get(int fd, long pos, char *buf, int n)
{
  lseek(fd, pos, 0); //get to pos
  return (read(fd, buf, n)); //read n bytes from current pos into the buffer return #bytes read
}
