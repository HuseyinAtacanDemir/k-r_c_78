#include <stdio.h>

int any(char *s1, char *s2);

main () {
  char s1[100] = "abcdefgh";
  char s2[100] = "ijklmh";


  printf("String1: %s\nString2: %s\nFirst Location: %d\n", s1, s2, any(s1,s2));
}


int any(char *s1, char *s2) {
  int i, j;
  for (i = 0; s1[i] != '\0'; i++)
    for (j = 0; s2[j] != '\0'; j++)
      if (s1[i] == s2[j])
        return i;
  return -1;
}
