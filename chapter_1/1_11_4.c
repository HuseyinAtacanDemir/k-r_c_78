#include <stdio.h>

#define MAXINPUT 1000

void remove_comments(char *in, char *out);

int main()
{
  char c;
  char input[MAXINPUT];
  char output[MAXINPUT];

  int i = 0;
  while((c=getchar()) != EOF)
    input[i++] = c;
  input[i] = '\0';

  remove_comments(input, output);
  
  printf("\n%s\n", output);
  
  return 0;
}

void remove_comments(char *in, char *out) {
  int double_quote = 0;
  int single_quote = 0;
  
  int comment = 0;

  char last_char = '\0';
  int i, j;
  i = j = 0;

  while (in[i] != '\0') {
    if (!comment && last_char != '\\' && in[i] == '\'')
      single_quote = !single_quote;
    if (!comment && last_char != '\\' && in[i] == '"')
      double_quote = !double_quote;

    if (!single_quote && !double_quote && last_char == '/' && in[i] == '*') {
      comment = 1;
      j--;
    }

    if(!comment) {
      last_char = in[i];
      out[j++] = in[i++];
    } else {
      if (comment && last_char == '*' && in[i] == '/')
        comment = 0;
      last_char = in[i];
      ++i;
    }
  }
  out[j] = '\0';
}
