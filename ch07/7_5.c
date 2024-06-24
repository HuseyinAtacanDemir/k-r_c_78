#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE     1000
#define DEF_LENGTH  100
#define DEF_WIDTH   100
#define help() { \
    fprintf(stderr, "page:\n\tUsage:\n\t\t./a.out [-l num>1] [-w num>0] [file ...]\n");\
    exit(1); \
}

#define file_err(msg) { \
    fprintf(stderr, "page: can't open file %s\n", *msg); \
    exit(1); \
}

#define strip_newline_at_end(c) { \
    char *p = (c);                \
    while (*p != '\0') {          \
      if(*p == '\n') {            \
        *p = '\0';                \
        break;                    \
      }                           \
      p++;                        \
    }                             \
}

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
void err(char *msg, int status);

main(int argc, char **argv)
{
  char line[MAXLINE], *c;
  FILE *fp;
  int length, width, page_no, line_no, overflow, i;
  
  length = DEF_LENGTH;
  width = DEF_WIDTH;

  while (--argc > 0 && (*++argv)[0] == '-') {
    if (*(argv[0]+1) == 'l') {
      if (argv[1] != NULL && isnumber(argv[1])) {
        length = atoi(argv[1]);
        --argc;
        ++argv;
      } else 
        help(); 
    } else if (*(argv[0]+1) == 'w') {
      if (argv[1] != NULL && isnumber(argv[1])) {
        width = atoi(argv[1]);
        --argc;
        ++argv;
      } else 
        help(); 
    } else
      help();
  }

  if (length <= 1 || width <= 0)
    help();

  if (argc >= 1) {
    while (argc-- > 0) {
      if ((fp = fopen(*argv, "r")) == NULL)
        file_err(argv);

      line_no = page_no = overflow = 0;
      while (fp != NULL) {
        if (line_no == 0 && page_no == 0)
          c = *argv;
        else 
          c = overflow != 0 ? c : fgets(line, MAXLINE, fp);
        
        if (c == NULL)
          break;

        strip_newline_at_end(c);
        int cur_line_len = strlen(c) - overflow; 

        if (line_no == length-1) {
          printf("%*d\n", width/2, page_no+1);
          line_no = 0;
          page_no++;
        }
        
        if (cur_line_len <= width) {
          for ( ; *(c+overflow) != '\0'; c++)
            putchar(*(c+overflow));
          putchar('\n');
          overflow = 0;
          line_no++;
        } else {
          i = 0;
          while (i < width && *(c+overflow+i) != '\0') {
            putchar(*(c+overflow+i));
            i++;
          }
          putchar('\n');
          if (*(c+overflow+i) == '\0')
            overflow = 0;
          else
            overflow += i;
          line_no++;
        }
      }

      if (line_no != 0) {
        while (line_no++ <= length-2)
          printf("\n");
        printf("%*d\n", width/2, page_no+1);
      }
      fclose(fp);
      argv++;
    }
  } else
    help();
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
