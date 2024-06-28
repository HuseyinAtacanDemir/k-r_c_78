#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define _BUFSIZE  512
#define _NFILE    20

typedef struct _iobuf {
  char *_ptr;   //next char position
  int _cnt;     //# of chars left
  char *_base;  //location of buf
  int _flag;    //mode of file access
  int _fd;      //file descriptor
} FILE;


#define _READ   01
#define _WRITE  02
#define _UNBUF  04
#define _BIGBUF 010
#define _EOF    020
#define _ERR    040
#define EOF     (-1)

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


FILE _iob[_NFILE] = {
  { NULL, 0, NULL, _READ, 0 },          //stdin
  { NULL, 0, NULL, _WRITE, 1 },         //stdout
  { NULL, 0, NULL, _WRITE | _UNBUF, 2}  //stderr
};

FILE *fopen_ex(register char *name, register char *mode);
int fclose_ex(register FILE *fp);
int _fillbuf(register FILE *fp);
int _flushbuf(int x, register FILE *fp);
int fflush_ex(register FILE *fp);

main()
{
  char *file_name = "test.txt";
  char c;
  FILE *fp = fopen_ex(file_name, "r");

  while ((c = getc(fp)) != EOF) {
    putchar(c);
  }
  fflush_ex(&_iob[1]);
  fclose_ex(fp);
  return 0;
}

/*
  we check for valid modes
  we find a suitable place for a new FILE *fp in _iob
  if mode is w we creat a new file
  if mode is a we open a file (if exists) or creat
    if it existed, we lseek to end of file
  if mode is r we just open it

  if fd is -1 we return NULL
  
  we set fp->_fd to fd
         fp->_cnt to 0
        etc...
*/
FILE *fopen_ex(register char *name, register char *mode)
{
  register int fd;
  register FILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    //fprintf(stderr, "illegal mode %s opening %s\n", mode, name);
    return (NULL);
  }

  for (fp =_iob; fp < _iob + _NFILE; fp++)
    if ((fp->_flag & (_READ | _WRITE)) == 0)
      break; //found empty slot
  
  if (fp >= _iob + _NFILE) //no free slots
    return (NULL);

  if (*mode == 'w')
    fd = creat(name, PMODE);
  else if (*mode == 'a') {
    if ((fd = open(name, 1)) == -1) {
      fd = creat(name, PMODE);
    } else {
      lseek(fd, 0L, 2);
    }
  } else
    fd = open(name, 0);

  if (fd == -1)
    return (NULL);

  fp->_fd = fd;
  fp->_cnt = 0;
  fp->_base = NULL;
  fp->_flag &= ~( _READ | _WRITE ); // zero the _READ and _WRITE bits
  fp->_flag |= (*mode == 'r') ? _READ : _WRITE;
  return (fp);
}

int fclose_ex(register FILE *fp)
{
  int rc;
  
  if ((rc = fflush_ex(fp)) != EOF) {
    free(fp->_base);
    fp->_base = NULL;
    fp->_ptr = NULL;
    fp->_cnt = 0;
    fp->_flag &= ~(_READ | _WRITE);
    rc = close(fp->_fd);
  }
  return rc;
}

int _fillbuf(register FILE *fp)
{
  static char smallbuf[_NFILE]; //for unbeffered IO

  if ((fp->_flag & _READ) == 0 || (fp->_flag & (_EOF | _ERR)) != 0)
    return (EOF);

  while (fp->_base == NULL)   //find buffer space
    if (fp->_flag & _UNBUF)   //is unbuffered
      fp->_base = &smallbuf[fp->_fd];
    else if ((fp->_base = calloc(_BUFSIZE, 1)) == NULL)
      fp->_flag |= _UNBUF;
    else
      fp->_flag |= _BIGBUF;
  
  fp->_ptr = fp->_base;
  fp->_cnt = read(fp->_fd, fp->_ptr,
                  fp->_flag & _UNBUF ? 1 : _BUFSIZE);
  
  if (--fp->_cnt < 0) {
    if (fp->_cnt == -1)
      fp->_flag |= _EOF;
    else
      fp->_flag |= _ERR;
    
    fp->_cnt = 0;
    return (EOF);
  }
  return (*fp->_ptr++ & 0377); //make char positive
}

int _flushbuf(int x, register FILE *fp)
{
  static char smallbuf[_NFILE];
  
  if (fp < _iob || fp >= _iob + _NFILE)
    return EOF;
  
  if ((fp->_flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;

  while (fp->_base == NULL)
    if (fp->_flag & _UNBUF) {
      fp->_ptr = fp->_base = &smallbuf[fp->_fd];
      fp->_ptr++;
    } else if ((fp->_base = calloc(_BUFSIZE, 1)) == NULL)
      fp->_flag |= _UNBUF;
    else {
      fp->_flag |= _BIGBUF;
      fp->_ptr = fp->_base + 1;
    }

  int count = fp->_ptr - fp->_base;
  if (write(fp->_fd, fp->_base, count) != count) {
    fp->_flag |= _ERR;
    return EOF;
  }

  fp->_ptr = fp->_base;
  *fp->_ptr++ = x;
  fp->_cnt = fp->_flag & _UNBUF ? 0 :_BUFSIZE - 1;
  return x;
}

int fflush_ex(register FILE *fp)
{
  int rc = 0;
  if (fp < _iob || fp >= _iob + _NFILE)
    return EOF;

  if (fp->_flag & _WRITE)
    rc = _flushbuf(0, fp);

  fp->_ptr = fp->_base;
  fp->_cnt = (fp->_flag & _UNBUF) ? 1 : _BUFSIZE;
  return rc;
}
