#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 512
// 0 is stdin, 1 is stdout, 2 is stderr
//file descriptors are integers that the OS keeps track of

int get_char();
int get_char_chunk();

main()
{
  char buf[BUFSIZE];
  int n;
  while ((n = read(0, buf, BUFSIZE)) > 0)
    write(1, buf, n);
}

int get_char() 
{
  char c;
  return ((read(0, &c, 1) > 0) ? (unsigned char) c : EOF);
}

int get_char_chunk()
{
  static char buf[BUFSIZE];
  static char *bufp = buf;
  static int n = 0;
  
  if (n == 0) {
    n = read(0, buf, BUFSIZE);
    bufp = buf;
  }
  return((--n > 0) ? (unsigned char) *bufp++ : EOF);
}
