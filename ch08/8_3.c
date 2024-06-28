#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define _BUFSIZE  512
#define _NFILE    20

typedef struct _flags {
  unsigned is_read  : 1;
  unsigned is_write : 1;
  unsigned is_unbuf : 1;
  unsigned is_buf   : 1;
  unsigned is_eof   : 1;
  unsigned is_err   : 1;
} FLAG;

typedef struct _iobuf {
  char *_ptr;   //next char position
  int _cnt;     //# of chars left
  char *_base;  //location of buf
  FLAG _flag;    //mode of file access
  int _fd;      //file descriptor
} FILE;


#define _READ   01
#define _WRITE  02
#define _UNBUF  04
#define _BIGBUF 010
#define _EOF    020
#define _ERR    040
#define EOF     (-1)

FILE _iob[_NFILE] = {
  { NULL, 0, NULL, {1, 0, 0, 0, 0, 0}, 0 }, //stdin
  { NULL, 0, NULL, {0, 1, 0, 0, 0, 0}, 1 }, //stdout
  { NULL, 0, NULL, {0, 1, 1, 0, 0, 0}, 2}   //stderr
};

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

#define getc(p) ( --(p)->_cnt >= 0 \
              ? *(p)->_ptr++ & 0377 : _fillbuf(p) )
#define getchar() getc(stdin)

#define putc(x,p) ( --(p)->_cnt >= 0 \
              ? *(p)->_ptr++ = (x) : _flushbuf((x), p) )
#define putchar(x) putc((x), stdout)

#define PMODE 0644 //rw for owner, r for group and system

main()
{
  return 0;
}

FILE *fopen_ex(register char *name, register char *mode)
{
  register int fd;
  register FILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    //fprintf(stderr, "illegal mode %s opening %s\n", mode, name);
    exit(1);
  }

  for (fp =_iob; fp < _iob + _NFILE; fp++)
    if (fp->_flag.is_read == 0 && fp->_flag.is_write == 0)
      break; //found empty slot
  
  if (fp >= _iob + _NFILE) //no free slots
    return (NULL);

  if (*mode == 'w')
    fd = creat(name, PMODE);
  else if (*mode == 'a') {
    if ((fd = open(name, 1)) == -1)
      fd = creat(name, PMODE);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, 0);

  if (fd == -1)
    return (NULL);

  fp->_fd = fd;
  fp->_cnt = 0;
  fp->_base = NULL;
  fp->_flag.is_unbuf = 0;
  fp->_flag.is_buf   = 0;
  fp->_flag.is_eof   = 0;
  fp->_flag.is_err   = 0;
  if (*mode == 'r') {
    fp->_flag.is_write = 0;
    fp->_flag.is_read  = 1;
  } else {
    fp->_flag.is_write = 1;
    fp->_flag.is_read  = 0;
  }
  return (fp);
}

int _fillbuf(register FILE *fp)
{
  static char smallbuf[_NFILE]; //for unbeffered IO

  if (fp->_flag.is_read == 0 || fp->_flag.is_eof == 1 || fp->_flag.is_err == 1)
    return (EOF);

  while (fp->_base == NULL)   //find buffer space
    if (fp->_flag.is_unbuf == 1)   //is unbuffered
      fp->_base = &smallbuf[fp->_fd];
    else if ((fp->_base = calloc(_BUFSIZE, 1)) == NULL)
      fp->_flag.is_unbuf = 1;
    else
      fp->_flag.is_buf = 1;
  
  fp->_ptr = fp->_base;
  fp->_cnt = read(fp->_fd, fp->_ptr,
                  fp->_flag.is_unbuf ? 1 : _BUFSIZE);
  
  if (--fp->_cnt < 0) {
    if (fp->_cnt == -1)
      fp->_flag.is_eof = 1;
    else
      fp->_flag.is_err = 1;
    
    fp->_cnt = 0;
    return (EOF);
  }
  return (*fp->_ptr++ & 0377); //make char positive
}
