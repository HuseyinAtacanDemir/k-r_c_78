#include <stdio.h>

main() { /* counts digits, white space, others */
  int c, i, nwhite, nother;
  int ndigit[10];

  nwhite = nother = 0;
  for (i = 0; i < 10; ++i)
    ndigit[i] = 0;

  while((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
      ++ndigit[c-'0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++nwhite;
    else
      ++nother;

  printf("\nDigits:");
  for(i = 0; i < 10; ++i)
      printf("\n%d: %d", i, ndigit[i]); 
  
  printf("\nWhite Space: %d\nOther: %d\n", nwhite, nother);
}
