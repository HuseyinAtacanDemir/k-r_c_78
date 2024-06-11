/*
  pseudo_code:
    read all the lines of input
    sort them
    print them in order
*/

#include <stdio.h>
#include <string.h>

#define LINES 100 /* max lines to be sorted */
#define MAXLEN 1000

#ifndef NULL
#   define NULL 0 /* pointer value for error report */
#endif

#define ALLOCSIZE 1000 /* size of available space */

int readlines(char *lineptr[], char lines[][MAXLEN+1], int maxlines);
int get_line(char *s, int lim); /* get line into s, return length */
void sort(char *v[], int n);
void writelines(char *lineptr[], int nlines);

char *alloc_custom(int n);
void free_custom(char *p); // free the storage pointed to by p
int str_cmp(char *s, char *t);
void str_cpy(char *t, char *s);
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free_custom position */

main()
{

  /*
    lineptr is an arr of LINES many elems, each elem is a ptr to a char, i.e. lineptrs[i] is a char ptr
    and *lineptr[i] accesses a char
  */
  char *lineptr[LINES]; /* ptrs to text lines */
  char lines[LINES][MAXLEN+1];
  int nlines; /* number of input lines read */

  if ((nlines = readlines(lineptr, lines, LINES)) >= 0) {
    sort(lineptr, nlines);
    writelines(lineptr, nlines);
  } 
  else
    printf("input too big to sort\n");
}

//*lineptr initially points to the first line, each increment advances it to the next line
void writelines(char *lineptr[], int nlines)
{
  printf("\nSorted Lines: \n");
  while (--nlines >= 0)
    printf("%s\n", *lineptr++);
}

int readlines(char *lineptr[], char lines[][MAXLEN+1], int maxlines)
{
  int len, nlines;
  char line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0) {
    if (nlines >= maxlines)
      return -1;
    else if (len > MAXLEN)
      return -1;
    else {
      line[len-1] = '\0';
      str_cpy(lines[nlines],line);
      lineptr[nlines] = lines[nlines];
      nlines++;
    }
  }
  return nlines;
}

int get_line(char *s, int lim) /* get line into s, return length */
{
    int c;
    int i = 0;
    for ( ; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return(i);
}

void sort(char *v[], int n)
{
  int gap, i, j;
  char *temp;

  for (gap = n/2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
      for (j = i-gap; j >= 0; j -= gap) {
        if (str_cmp(v[j], v[j+gap]) <= 0)
          break;
        temp = v[j];
        v[j] = v[j+gap];
        v[j+gap] = temp;
      }
}

char *alloc_custom(int n)
{
  if (allocp + n <= allocbuf + ALLOCSIZE) { //fits
    allocp += n;
    return (allocp - n); // old p
  } else // not enough room
    return (NULL);
}

void free_custom(char *p) // free the storage pointed to by p
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

// go as far as possible while both values are the same, once they differ, return the difference
// if s was bigger, the result will be >0
// if equal =0
// if t bigger <0
int str_cmp(char *s, char *t)
{
  for ( ; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;
  return (*s - *t);
}

void str_cpy(char *t, char *s)
{
  while ((*t++ = *s++))
    ;
}
