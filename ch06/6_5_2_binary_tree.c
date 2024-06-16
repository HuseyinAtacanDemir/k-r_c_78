#include <stdio.h>
#include "6_5_2_tree.h"
#include "6_5_2_getword.h"

/*
  Suppose we want to handle the more general problem of counting the occurrences of all the words in some input.
  Since the list of words isn't knwon in advance, we can't conveniently sort it and use a binary search.
  Yet we can't do a linear search for each word as it arrives, to see if it's already been seen; the program 
  would take forever [more precisely, its expected running time would grow quadratically with the number of input words] 
  
  One solution is to keep the set of words seen so far sorted at all times, by placing each word into its proper position
  in the order as it arrives. This should not be done by shifting words in a linear array though, that also takes too long.
  Instead we will use a data structure called a binary tree.
*/

main()
{
  struct tnode *root;
  char word[MAXWORD];
  int t;

  root = NULL;
  while ((t = getword(word, MAXWORD)) != EOF)
    if (t == LETTER)
      root = insert(root, word);

  treeprint(root);
  treeprint_2d(root, 0);
}
