#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE_LEN 50

main(int argc, char **argv)
{
  int max_line_len = argc == 2 ? atoi(argv[1]) : MAX_LINE_LEN;
  int line_len = 0;
  char c;
  while ((c = getchar()) != EOF) {
    if (c >= 0x20 && c <= 0x7E) {
      if (line_len + 1 >= max_line_len) {
        line_len = 0;
        printf("\n");
      }
      printf("%c", c);
      line_len++;
    } else {
      if (line_len + 4 >= max_line_len) {
        line_len = 0;
        printf("\n");
      }
      printf("0x%.2x", c);
      line_len += 4;
    }
  }
}

