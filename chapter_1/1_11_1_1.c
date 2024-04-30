#include <stdio.h>

#define MAXINPUT 1000
#define TABSTOP 16

main()
{
  char input[MAXINPUT];
  char detabbed[MAXINPUT];
  int i, pos, bc;
  char c = EOF;
  
  i = pos = bc = 0;
  while ((c = getchar()) != EOF && i < MAXINPUT) {
    if (c == '\t') {
      bc = TABSTOP - (pos % TABSTOP);

        for (; bc > 0; --bc, ++pos)
          input[i++] = ' ';

    } else if (c == '\n') {
      input[i++] = '\n';
      pos = 0;
    } else {
      input[i++] = c;
      ++pos; 
    } 
  }
  printf("\n\n Detabbed Input: \n%s\n", input);
}

