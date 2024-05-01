#include <stdio.h>

#define MAXINPUT 1000

void check_syntax(char *in);
char reverse_bracket(char c);
int is_open_bracket(char c);
int is_close_bracket(char c);
void assert_expected(char *in, int row_seen, int col_seen, char *expected_str);

int main()
{
  char c;
  char input[MAXINPUT];

  int i = 0;
  while((c=getchar()) != EOF)
    input[i++] = c;
  input[i] = EOF;

  check_syntax(input);
  return 0;
}

void check_syntax(char *in) {
  int double_quote = 0;
  int dq_r = 0;
  int dq_c = 0;

  int single_quote = 0;
  int sq_r = 0;
  int sq_c = 0;

  int comment = 0;
  int c_r = 0;
  int c_c = 0;

  char brackets[MAXINPUT][4];
  brackets[0][0] = 0;
  int bracket_count = 0;

  char last_char = '\0';
  int i, row, col;
  i = row = col = 0;
  while (in[i] != EOF) {
    if (!comment && !double_quote && last_char != '\\' && in[i] == '\'') {
      if (single_quote)
        single_quote = 0;
      else {
        single_quote = i;
        sq_r = row;
        sq_c = col;
      }
    }
    if (!comment && !single_quote && last_char != '\\' && in[i] == '"') {
      if (double_quote)
        double_quote = 0;
      else {
        double_quote = i;
        dq_r = row;
        dq_c = col;
      } 
    }

    if (!comment && !single_quote && !double_quote && is_open_bracket(in[i])) {
      brackets[bracket_count][0] = in[i];
      brackets[bracket_count][1] = i;
      brackets[bracket_count][2] = row;
      brackets[bracket_count][3] = col;
      bracket_count++;
    }

    if (!comment && !single_quote && !double_quote && is_close_bracket(in[i])) {
      if (bracket_count > 0 && brackets[bracket_count - 1][0] == reverse_bracket(in[i])) {
        brackets[bracket_count - 1][0] = 0;
        brackets[bracket_count - 1][1] = 0;
        brackets[bracket_count - 1][2] = 0;
        brackets[bracket_count - 1][3] = 0;
        bracket_count--;
      } else {  
        brackets[bracket_count][0] = in[i];
        brackets[bracket_count][1] = i;
        brackets[bracket_count][2] = row;
        brackets[bracket_count][3] = col;
        bracket_count++;
      }
    }

    if (!single_quote && !double_quote && last_char == '/' && in[i] == '*') {
      comment = i;
      c_r = row;
      c_c = col;
    }

    if (comment && last_char == '*' && in[i] == '/')
      comment = 0;
    
    ++col;
    if(in[i] == '\n') {
      ++row;
      col = 0;
    }
    if(last_char == '\\' && in[i] == '\\')
      last_char = ' ';
    else
      last_char = in[i];
    i++;
  }

  if (double_quote) 
    assert_expected(in, dq_r, dq_c, "\"");
  if (single_quote)
    assert_expected(in, sq_r, sq_c, "'");
  if (comment)
    assert_expected(in, c_r, c_c, "*/");
  if (bracket_count) {
    i = 0;
    while(i < bracket_count) {
      char expected[2];
      expected[0] = reverse_bracket(brackets[i][0]);
      expected[1] = '\0';
      assert_expected(in, brackets[i][2], brackets[i][3], expected);
      i++;
    }
  }
  if (!double_quote && !single_quote && !comment && !bracket_count)
    printf("\nSyntax Check Passed!\n");  
}

void assert_expected(char *in, int row_seen, int col_seen, char *expected_str) {
    char preview[MAXINPUT];
    int row = row_seen;
    int col = 0;
    int k = 0;
    while (in[k] != EOF && row > 0) {
      if (in[k++] == '\n')
        row--;
    }
    col = 0;
    while (in[k] != EOF && in[k] != '\n')
      preview[col++] = in[k++];
    
    preview[col] = '\0';
    printf("\nRow: %d Col: %d. Expected %s, %s", row_seen, col_seen, expected_str, preview);
}

char reverse_bracket(char c) {
  if (c == '[')
    return ']';
  if (c == '{')
    return '}';
  if (c == '(')
    return ')';
  if (c == ']')
    return '[';
  if (c == '}')
    return '{';
  if (c == ')')
    return '(';
    
  return 'x';
}

int is_bracket(char c) {
  return (is_open_bracket(c) || is_close_bracket(c));
}

int is_open_bracket(char c) {
  if (c == '[' || c == '{' || c == '(')
     return 1;
  return 0;
}

int is_close_bracket(char c) {
  if(is_open_bracket(reverse_bracket(c)))
    return 1;
  return 0;
}
