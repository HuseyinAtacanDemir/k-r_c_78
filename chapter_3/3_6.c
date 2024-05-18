#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 1000

/*
  get input char by char
  get a rolling line len count
  
  start processing for a next line when \n is encountered
  store the line len count of the prev line
  using the stored prev line len, print the prev line as a str

  when you're in the next line state, 
  using the prev line len, cross check each new char with the currentIdx - line Len 
  to check for an identical line
    skip printing iff \n was encountered at position curIdx-lineLen == 0
      reset line len
      move onto next line processing 

*/

void uniq();

main(){
  uniq();
}

void uniq()
{
  int prev_line_len = 0;
  int line_len = 0;
  int i = 0;

  char input [MAX_INPUT_LEN];
  char c;
  while ((c = getchar()) != EOF) {
    line_len++;
    input[i] = c;
    if( c == '\n') {
      if (prev_line_len == line_len) {
        i -= line_len;
        printf("\n");
      } else {
        prev_line_len = line_len;
        line_len = 0;
        char s[prev_line_len + 1];
        int j = 0;
        while (j <= prev_line_len){
          s[j] = input[i-prev_line_len + j];
          j++;
        }
        s[j] = '\0';
        printf("%s", s);
      }
    }
    i++;
  }
  input[i] = '\0';
  printf("\n\nInput:\n%s\nInputEnd\n", input);
}
