#include <stdio.h>

main(){
  char c;
  int lim = 1000;
  
  int i = 0;
  while (i < lim - 1) {
    c = getchar();
    if (c == '\n')
      break;
    else if (c == '\0')
      break;
    s[i++] = c;
  }

}
