#include <stdio.h>

void squeeze(char *s1, char *s2);

main() {
  char s1[100] = "abc abc abc abc abc";
  char s2[100] = "a ";

  squeeze(s1, s2);

  printf("%s\n", s1);
}

void squeeze(char *s1, char *s2) {
  int i, j, k;
  for (i = j = 0; s1[i] != '\0'; i++) {
    int isInStr2 = 0;
    for(k = 0; s2[k] != '\0'; k++)
      if (s1[i] == s2[k]) isInStr2 = 1;
    if (!isInStr2)
      s1[j++] = s1[i]; 
  }
  s1[j] = '\0';
}
