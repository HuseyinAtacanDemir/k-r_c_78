#include <stdio.h>

main(){
  int blank = 0, tab = 0, newLine = 0;
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\t')
      ++tab;
    if (c == '\n')
      ++newLine;
    if (c == ' ')
      ++blank;
  }
  printf("\nBlanks: %d\nTabs: %d\nNew Lines: %d\n", blank, tab, newLine);

}
