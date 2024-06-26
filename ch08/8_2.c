#include <unistd.h>

#define BLOCKSIZE 512
#define MAX_SIZE  65535
int seek_with_lseek(int fd, int offset, unsigned char origin)
{
  if (origin < 0 || origin > 5)
    return -1;
  return lseek(fd, origin < 3 ? offset : offset * BLOCKSIZE, (origin % 3));
}

int lseek_with_seek(int fd, long offset, unsigned char origin)
{
  int intermediary_offset, multiplier, retval;

  if (offset <= MAXSIZE)
    return seek(fd, (int) offset, origin);
  
  intermediary_offset = offset;
  multiplier = 0;
  while (intermediary_offset > BLOCKSIZE) {
    intermediary_offset -= BLOCKSIZE;
    multiplier++;
  }
  retval = seek(fd, multiplier, ((origin % 3) + 3));
  
  if (retval < 0)
    return -1;
  
  return seek(fd, (offset-(multiplier*BLOCKSIZE)), origin);
}
