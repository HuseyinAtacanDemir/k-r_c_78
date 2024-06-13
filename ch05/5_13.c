#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINES     100
#define MAX_LINE_LEN  100
#define MEM_SIZE      1000

void sort(char *[], int , int (*)(), void (*)());
void swap(char **, char **);
int num_cmp(char *, char *);
int str_cmp(char *, char *);

int readargs(int, char *[]);
int read_lines(char *[], int);
void write_lines(char *[], int, int);
int get_line(char *, int);
char *alloc_mem(int);

static char mem_buf[MEM_SIZE];
static char *mem_ptr = mem_buf;

static char options = 0;

int main (int argc, char *argv[])
{
  char *lineptr[MAX_LINES];
  int nlines;
  int rc = 0; 
  
  rc = readargs(argc, argv);
  if (!rc) {
    if ((nlines = read_lines(lineptr, MAX_LINES)) >= 0) {
      if (options & 0x1) 
        sort(lineptr, nlines, num_cmp, swap);
      else
        sort(lineptr, nlines, str_cmp, swap);
      write_lines(lineptr, nlines, options & 0x2);
    } else {
      printf("Input too big\n");
      rc = -1;
    }
  }
  return rc;
}

int readargs(int argc, char *argv[])
{
  int c, rc = 0;
  
  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++argv[0])) {
      switch (c) {
        case 'n':
          options |= 0x1;
          break;
        case 'r':
          options |= 0x2;
          break;
        case 'f':
          options |= 0x4;
          break;
        case 'd':
          options |= 0x8;
          break;
      default:
          printf("sort: Illegal Option %c\n", c);
          argc = 1;
          rc = -1;
          break;
      }
    }
  }
  if (argc) {
    printf("Usage: \nsort <enter for stdin or filename>\nsort -n -r\t\t-n for numeric, -r for reverse order\nsort -nr");
    rc = -1;
   }
  return rc;
}

void sort(char *v[], int n, int (*comp)(const char *, const char *), void (*exch)(char **, char **))
{
  int gap, i, j;
  
  for (gap = n/2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
      for (j = i-gap; j >= 0; j -= gap) {
        if ((*comp)(v[j], v[j+gap]) <= 0)
          break;
        (*exch)(&v[j], &v[j+gap]);
      }
}

int str_cmp(char *s, char *t)
{
  char a, b;
  int case_insensitive, dir;
  
  case_insensitive = options & 0x4;
  dir = options & 0x8;
   
  do {
    if (dir) {
      while (!isalnum(*s) && *s != ' ' && *s != '\0')
        s++;
      while (!isalnum(*t) && *t != ' ' && *t != '\0')
        t++;
    }
    a = case_insensitive ? tolower(*s) : *s;
    s++;
    b = case_insensitive ? tolower(*t) : *t;
    t++;

    if (a == b && a == '\0')
      return 0;
  } while (a == b);
  return (a - b);
}

int num_cmp(char *s, char *t)
{
  double v1, v2;

  v1 = atof(s);
  v2 = atof(t);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  return 0;
}

/*
  we need to swap the pointers that point to the start of the lines in the main line_ptrs arr
  thus, we give the addresses of the ptrs that we need to swap to the swap fn
  therefore, the effectively give ptrs to ptrs.
  we give the address in the line_ptr arr of these ptrs that point to specific strings.
*/
void swap(char **px, char **py)
{
  char *temp = *px;
  *px = *py;
  *py = temp;
}

int read_lines(char *line_ptrs[], int max_line_count)
{
  int cur_line_len, line_count;
  char *cur_line_ptr, cur_line[MAX_LINE_LEN];
  
  line_count = 0;
  while ((cur_line_len = get_line(cur_line, MAX_LINE_LEN)) > 0) {
    if (line_count >= max_line_count)
      return -1;
    else if ((cur_line_ptr = alloc_mem(cur_line_len+1)) == NULL)
      return -1;
    else {
      strcpy(cur_line_ptr, cur_line);
      line_ptrs[line_count++] = cur_line_ptr;
    }
  }
  return line_count;
}

void write_lines(char *lineptr[], int nlines, int option)
{
  int i = option ? nlines-1 : 0;
  for ( ; option ? i >= 0 : i < nlines; option ? i-- : i++)
    printf("%s\n", lineptr[i]);
}

int get_line(char *s, int max_line_len)
{
  char *p, c;

  p = s;
  while (max_line_len-- > 2 && (c=getchar()) != EOF && c != '\n')
    *s++ = c;

  if (c == '\n' || (c == EOF && s > p && *(s-1) != '\n'))
    *s++ = '\n';

  *s = '\0';
  return (s - p);
}

char *alloc_mem(int size)
{
  char *allocated_mem_ptr;
  if (mem_ptr + size < mem_buf + MEM_SIZE) {
    allocated_mem_ptr = mem_ptr;
    mem_ptr += size;
    return allocated_mem_ptr;
  }
  return NULL;
}


