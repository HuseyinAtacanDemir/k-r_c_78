#include <stdio.h>

#define YES 1
#define NO  0

main() /* count lines, words, chars in input */
{
    int c, nl, nw, nc, inword;

    inword = NO;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc; /* incerement char count in any case*/
        if (c == '\n' ) /* increment line count at each \n*/
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t' ) /* boundaries for deciding ending a word*/
            inword = NO;
        else if ( inword == NO && ((c >=65 && c <= 90) || (c >= 97 && c <= 122)) ) { 
            /* boundaries for defining the start of a new word A-Za-z*/
            inword = YES;
            ++nw;
        } else if ( inword == YES && !((c >=65 && c <= 90) || (c >= 97 && c <= 122) || (c>=48 && c<=57) || c == 39)) { 
          /* boundaries for discounting a word: if c is NOT in A-Z or a-z or 0-9 or ' */
          inword = NO;
          --nw;
        }
    }
    printf("\nLine Count: %d, Word Count: %d, Char Count: %d\n", nl, nw, nc);
}
