#include <stdio.h>

char lower(char in);

main(){
  char a = 'F';

  printf("U: %c, l: %c\n", a, lower(a));

}
char lower(char in) {
  return ( (in >= 'A' && in <= 'Z') ? in + ('a' - 'A') : in );
}
