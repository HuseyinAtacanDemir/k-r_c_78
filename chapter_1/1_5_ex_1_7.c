#include <stdio.h>

main(){
  int blank_again = 0;

  int c;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (blank_again == 0) {
         blank_again = 1;
         putchar(c);
      }
    } else {
      blank_again = 0;
      putchar(c);
    }
  }
}
