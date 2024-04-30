#include <stdio.h>

#define MAXINPUT 1000
#define TABSIZE 8

main(){
  int i, c, bc, tc, pos;
  char input[MAXINPUT];

  i = bc = tc = pos = 0;

   for(pos = 1; (c=getchar())!=EOF; ++pos)
      if (c == ' ') {
        if (pos % TABSIZE != 0)
          ++bc;
        else {
          bc = 0;
          ++tc;
        }
      } else {
        for (; tc > 0; --tc)
          input[i++] = '\t';

        if (c == '\t')
          bc = 0;
        else
          for (; bc > 0; --bc)
            input[i++] = ' ';
        input[i++] = c;
        
        if (c == '\n')
          pos = 0;
        else if (c == '\t')
          pos = pos + (TABSIZE - (pos - 1) % TABSIZE) - 1;
      }
  printf("\nOutput: \n%s\n", input);
}
