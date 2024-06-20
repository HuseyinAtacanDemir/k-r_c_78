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
main(int argc, char **argv)
{

  char line[MAXLINE], *c;

  int line_no = 0;
  int char_pos = 0;
  int page_no = 0;

  int length = DEF_LENGTH;
  int width = DEF_WIDTH; 
  
  while (--argc > 0 && (*++argv)[0] == '-')
    char *s, *p, *arg;
    p = argv[0];
    for (s = p+1; *s != '\0'; s++)
      switch (*s) {
        arg = (argv+(s-p));
        case 'l':
          if (!isnumber(*arg)) {
            fprintf(stderr, "page: Illegal line length value %s\n", *arg);
            exit(1);
          }
          length = atoi(*arg);
          break;
        case 'w':
          if (!isnumber(*arg)) {
            fprintf(stderr, "page: Illegal line length value %s\n", *arg);
            exit(1);
          }
          width = atoi(*arg);
          break;
        default:
          fprintf(stderr, "page: Illegal option %c\n", *s);
          exit(1);
      }

  if (argc > 1) {
    while (--argc > 0) {
      FILE *fp = fopen(*argv, "r");
      if (fp == NULL) {
        fprintf(stderr, "page: can't open %s\n", *argv);
        exit(1);
      }
      while (fp != NULL && (c = fgets(line, MAXLINE, fp)) != NULL) {
        
      }
      line_no = char_pos = page_no = 0;
      fclose(fp);
      argv++;
    }
  } else {
    fprintf(stderr, "page:\n\tUsage:\n\t\t./a.out [-l num] [-w num] [file ...]\n");
    exit(1);
  }
}
