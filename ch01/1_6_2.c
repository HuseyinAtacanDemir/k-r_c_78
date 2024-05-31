#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define HORZ 1
#define VERT 0

#define MAX_WORD_LEN 15

int max(int *histogram_data)
{
  int cur_max = 0, i = 0;
  for (i = 0; i < MAX_WORD_LEN + 1; ++i)
    if ( histogram_data[i] > cur_max)
      cur_max = histogram_data[i];
  return cur_max;
}
 
void draw_histogram(int *histogram_data, int orientation)
{
  printf("\n\n\nWord Count Histogram\n\n");
  int i, j;
  if ( orientation == VERT ) {
    int max_input_word_len = max(histogram_data);
    for (i = max_input_word_len + 1; i > 0; --i) { 
      /* 1 line buffer to write the totals on top of each histogram bar*/
      for (j = 0; j < MAX_WORD_LEN + 1; ++j) 
        if (histogram_data[j] >= i)
          printf("   ##  ");
        else if (histogram_data[j] != 0 && histogram_data[j] == i-1)
          printf("   %2d  ", histogram_data[j]);
        else
          printf("       "); 
      
      printf("\n");
    }
    for (i = 0; i < MAX_WORD_LEN + 1; ++i) 
      if (i == MAX_WORD_LEN)
        printf("--------\n");
      else
        printf("-------");
    for (i = 0; i < MAX_WORD_LEN + 1; ++i) 
      if (i == MAX_WORD_LEN)
        printf("| >%d  |\n", MAX_WORD_LEN);
      else
        printf("|%4d  ", i+1);
    
  } else if ( orientation == HORZ ) {
    printf(" Len | Count in Input\n");
    for (i = 0; i < MAX_WORD_LEN + 1; ++i) {
      if (i == MAX_WORD_LEN)
        printf(" >%d | ", MAX_WORD_LEN);
      else
        printf("%4d | ", i+1);
      for (j = 0; j < histogram_data[i]; ++j)
        printf("#");
      if (histogram_data[i] != 0)
        printf(" %d\n", histogram_data[i]);
      else
        printf("\n");
    }
  } else
    printf("Unrecognized Histogram Orientation...\n");
} 

main() /* count lines, words, chars in input */
{
  int c, nw, nc, inword;
  int histogram_data[MAX_WORD_LEN + 1];

  for(c = 0; c <= MAX_WORD_LEN; ++c)
    histogram_data[c] = 0;
  
  inword = FALSE;
  nw = nc = c = 0;
  while ((c = getchar()) != EOF) {
      if (c == ' ' || c == '\n' || c == '\t' ) { /* boundaries for deciding ending a word*/
        if ( nc < MAX_WORD_LEN && nc > 0) 
          ++histogram_data[nc - 1];
        else if ( nc >= MAX_WORD_LEN )
          ++histogram_data[MAX_WORD_LEN];
        nc = 0;
        inword = FALSE;
      } else if ( inword == FALSE && ((c >=65 && c <= 90) || (c >= 97 && c <= 122)) ) { 
          /* boundaries for defining the start of a new word A-Za-z*/
          inword = TRUE;
          ++nw;
          ++nc; /* increment char count when we enter a word*/
      } else if ( inword == TRUE && !((c >=65 && c <= 90) || (c >= 97 && c <= 122) || (c>=48 && c<=57) || c == 39)) { 
        /* boundaries for discounting a word: if c is FALSET in A-Z or a-z or 0-9 or ' */
        inword = FALSE;
        --nw;
        nc = 0; /* discard the running char count since the word was discounted*/
      } else if ( inword == TRUE ) {
        /* increment char count while still in a word for each char*/
        ++nc;
      }
  }
  draw_histogram(histogram_data, HORZ);
  draw_histogram(histogram_data, VERT);
}
