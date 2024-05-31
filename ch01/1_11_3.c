#include <stdio.h>

#define MAXINPUT 1000
#define LINECUTOFF 40

int fold(char *s, int j, int line_cutoff);
int is_blank(char c);

int main() 
{
  int i, pos;
  char c;
  char input[MAXINPUT];

  i = pos = 0;
  while((c=getchar())!= EOF) {
    input[i] = c;

    if (c == '\n')
      pos = -1;
    
    if (pos == LINECUTOFF) {
      int old_len = i;
      i = fold(input, i, LINECUTOFF);
      pos = i - old_len - 1;
    }

    ++i;
    ++pos;
  }

  input[i] = '\0';

  printf("\n%s\n", input);
  return 0;
}

int fold(char *s, int j, int line_cutoff) {
  int i;
  int len = j;
  for (i = 0; len - j < line_cutoff; --j, ++i) {
    if (is_blank(s[j])) {
      s[j] = '\n';
      return len;
    }
  }
  
  char last = s[len];
  s[len] = '\n';
  s[len+1] = '.';
  s[len+2] = '.';
  s[len+3] = '.';
  s[len+4] = last;

  return len + 4;
}

int is_blank(char c) {
  if(c == ' ')
    return 1;
  if(c == '\t')
    return 1;
  return 0;
}
