#include <stdio.h>

#define MAXINPUT 1000
#define TABSIZE 4

void detab(char *s1, char *s2, int tab_size);

main()
{
  char input[MAXINPUT];
  char detabbed[MAXINPUT];
  
  char c = EOF;
  int i = 0;
  while ((c = getchar()) != EOF && i < MAXINPUT)
    input[i++] = c;

  detab(input, detabbed, TABSIZE);
  printf("\nDetabbed: \n%s\n", detabbed);

  printf("\n\n Original Input: \n%s\n", input);
}

void detab(char *s1, char *s2, int tab_size)
{
  int i, j, k;

  i = j = k = 0;
  while (s1[i] != '\0') {
    if (s1[i] == '\t')
      for (k = 0; k < tab_size; ++k)
        s2[j++] = ' ';
    else
      s2[j++] = s1[i];

    ++i;
  }
  s2[j] = '\0';
}
