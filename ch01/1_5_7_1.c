#include <stdio.h>

main(){
  int c;
  int last_c = 0;
  while((c = getchar()) != EOF) {
    if (c == '\t' || c == '\n' || c == ' ') {
      if (last_c == 0)
        putchar('\n');
      last_c = 1;
    } else {
      putchar(c);
      last_c = 0;
    }
  }
}
