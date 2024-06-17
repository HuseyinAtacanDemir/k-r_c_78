#include <stdio.h>
#include "6_5_tree.h"
#include "6_5_2_getword.h"

main()
{
  struct tnode *root;
  char word[MAXWORD];
  int t;
  int line;

  line = 1;
  root = NULL;
  while ((t = getword_with_line(word, &line, MAXWORD)) != EOF)
    if (t == LETTER)
      root = insert(root, word, line);

  treeprint(root);
  treeprint_2d(root, 0);
}
