#include <unistd.h>

#define BUFSIZE 512

// 0 is stdin, 1 is stdout, 2 is stderr
//file descriptors are integers that the OS keeps track of

main()
{
  char buf[BUFSIZE];
  int n;
  while ((n = read(0, buf, BUFSIZE)) > 0)
    write(1, buf, n);
}
