#include <stdio.h>

main(){
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\b') {
      putchar('<');
      putchar('-');
    } else if (c == '\t') {
      putchar('>');
      putchar('-');
    } else {
      putchar(c);
    }
  }
}
