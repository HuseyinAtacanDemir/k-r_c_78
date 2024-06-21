#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE     1000
#define DEF_LENGTH  100
#define DEF_WIDTH   100

/*
NAME
  ./a.out

SYNOPSIS
  ./a.out [-l num] [-w num] [file ...]

DESCRIPTION

  Takes any given input files, concatenates them into "pages" of specified amount of lines [-l num], integer describing height by lines (100 lines by default), 
  and a width [-w num] parameter, integer describing width by chars (100 chars by default). Each file is prepended with its name and each file will start at a
  new "page".
  
*/

int isnumber(char *);
int copy_substr(char *, char *, int, int);
main(int argc, char **argv)
{

  char line[MAXLINE], line_overflow[MAXLINE], *c;

  int line_no = 0;
  int char_pos = 0;
  int page_no = 0;

  int length = DEF_LENGTH;
  int width = DEF_WIDTH; 
  int i = 0;
    
  while (--argc > 0 && (*++argv)[0] == '-') {
    if (*(argv[0]+1) == 'l') {
      if (argv[1] != NULL && isnumber(argv[1])) {
        length = atoi(argv[1]);
        --argc;
        ++argv;
      } else {
        fprintf(stderr, "page:\n\tUsage:\n\t\t./a.out [-l num] [-w num] [file ...]\n");
        exit(1);
      }
    } else if (*(argv[0]+1) == 'w') {
      if (argv[1] != NULL && isnumber(argv[1])) {
        width = atoi(argv[1]);
        --argc;
        ++argv;
      } else {
        fprintf(stderr, "page:\n\tUsage:\n\t\t./a.out [-l num] [-w num] [file ...]\n");
        exit(1);
      }
    }
  }

  if (argc > 1) {
    while (--argc > 0) {
      FILE *fp = fopen(*argv, "r");
      if (fp == NULL) {
        fprintf(stderr, "page: can't open %s\n", *argv);
        exit(1);
      }
      line_no = page_no = 0;
      while (fp != NULL && (c = line_overflow[0] ? line_overflow : fgets(line, MAXLINE, fp)) != NULL) {
        int cur_line_len = strlen(c);
        if (line_no == 0 && page_no == 0) {
          printf("%*s\n", (int)((width-strlen(*argv))/2), *argv);
          line_no++;
        } else if (line_no == length-1) {
          printf("%*d\n", width/2, page_no+1);
          line_no = 0;
          page_no++;
        }
        
        if (cur_line_len < width){
          printf("%s", c);
          line_no++;
          line_overflow[0] = '\0';
        } else {
          copy_substr(line_overflow, line, (width-2), -1);
          line[width-2] = '\n';
          line[width-1] = '\0';
          printf("%s", c);
          line_no++;
        }
        
      }
      if (line_no != 0) {
        while (line_no != 0 && line_no++ < length-2)
          printf("\n");
        printf("%*d\n", width/2, page_no+1);
      }
      fclose(fp);
      argv++;
    }
  } else {
    fprintf(stderr, "page:\n\tUsage:\n\t\t./a.out [-l num] [-w num] [file ...]\n");
    exit(1);
  }
}

int isnumber(char *s) {
  while (*s) {
    if (*s >= 0x30 && *s < 0x39) {
      s++;
    } else {
      return 0;
    }
 }
  return 1;
}

int copy_substr(char *s, char *p, int start, int end)
{
  if (end == -1) {
    end = strlen(p);
  }
  if(start >= strlen(p)) {
    fprintf(stderr, "copy_substr: invalid start index: %d for str with len len: %lu\n", start, strlen(p));
    return 1;
  }
  if(end > strlen(p)) {
    fprintf(stderr, "substr: invalid end index: %d for str with len: %lu\n", end, strlen(p));
    return 1;
  }
  
  if (start > end) {
    fprintf(stderr, "copy_substr: invalid indexes, start index: %d cannot be bigger than end index: %d\n", start, end);
    return 1;
  }
  
  for ( ; start<=end; start++) {
    *s++ = *(p+start);
  }
  *s = '\0';
  return 0;
}
