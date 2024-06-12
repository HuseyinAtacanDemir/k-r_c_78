#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_TAIL_LEN  10
#define MAX_LINES         100
#define MAX_LINE_LEN      100
#define MEM_SIZE          1000

void tail_lines(char *[], int, int);
int read_lines(char *[], int);
int get_line(char *, int);
char *alloc_mem(int);
void throw_error(char *);

char *message = "Usage:\n\ntail\ntail -n <line_count>\n";

static char mem_buf[MEM_SIZE];
static char *mem_ptr = mem_buf;

main(int argc, char **argv)
{
  char *p, *line_ptrs[MAX_LINES];
  int line_count, tail_len;

  tail_len = DEFAULT_TAIL_LEN;
  if(argc == 3 && !strcmp(argv[1], "-n"))
    tail_len = atoi(argv[2]); 
  else if (argc != 1)
    throw_error(message);

  line_count = read_lines(line_ptrs, MAX_LINES);
  tail_lines(line_ptrs, line_count, tail_len);

}

void throw_error(char *error_message)
{
  printf("%s", error_message);
  exit(1);
}

void tail_lines(char *line_ptrs[], int line_count, int tail_len)
{
  if(tail_len > MAX_LINES)
    tail_len = MAX_LINES;
  if(tail_len > line_count)
    tail_len = line_count;
  printf("result\n");
  while (tail_len-- > 0)
    printf("%s\n", line_ptrs[line_count-1-tail_len]);
}

int read_lines(char *line_ptrs[], int max_line_count)
{
  int cur_line_len, line_count;
  char *cur_line_ptr, cur_line[MAX_LINE_LEN];
  
  line_count = 0;
  while ((cur_line_len = get_line(cur_line, MAX_LINE_LEN)) > 0) {
    if (line_count >= max_line_count)
      return -1;
    else if ((cur_line_ptr = alloc_mem(cur_line_len)) == NULL)
      return -1;
    else {
      cur_line[cur_line_len -1] = '\0';
      strcpy(cur_line_ptr, cur_line);
      line_ptrs[line_count++] = cur_line_ptr;
    }
  }
  return line_count;
}

int get_line(char *s, int max_line_len)
{
  char *p, c;

  p = s;
  while (max_line_len-- > 2 && (c=getchar()) != EOF && c != '\n')
    *s++ = c;

  if (c == '\n')
    *s++ = c;

  *s = '\0';
  return (s - p);
}

char *alloc_mem(int size)
{
  char *allocated_mem_ptr;
  if (mem_ptr + size <= mem_buf + MEM_SIZE) {
    allocated_mem_ptr = mem_ptr;
    mem_ptr += size;
    return allocated_mem_ptr;
  }
  return NULL;
}
