#include <stdio.h>
#include <string.h>

void expand(char *s1, char *s2);
void append_range(char a, char b, char *s, int index);
main ()
{
  char in[100];
  char out[100];

  char c;
  int i = 0;
  while((c=getchar())!= EOF)
    in[i++] = c;
  in[i] = '\0';

  expand(in, out);
  printf("\n%s\n", out);
}

void expand(char *s1, char *s2)
{
  int i;
  int j;
  for (i = 0, j = 0; i <= strlen(s1) - 1; i++) {
    if (s1[i] >= 'a' && s1[i] <= 'z' && i < (strlen(s1) - 3) ){
      if (s1[i+1] == '-' && (s1[i+2] >= 'a' && s1[i+2] <= 'z') && s1[i+2] - s1[i] > 1) {
        append_range(s1[i], s1[i+2], s2, j);
        j += (1 + s1[i+2] - s1[i]);
        i += 2;
        continue;
      }
    } 
    else if (s1[i] >= 'A' && s1[i] <= 'Z' && i < (strlen(s1) - 3)){
      if (s1[i+1] == '-' && (s1[i+2] >= 'A' && s1[i+2] <= 'Z') && s1[i+2] - s1[i] > 1) {
        append_range(s1[i], s1[i+2], s2, j);
        j += (1 + s1[i+2] - s1[i]);
        i += 2;
        continue;
      }
    }
    else if (s1[i] >= '0' && s1[i] <= '9' && i < (strlen(s1) - 3)){
      if (s1[i+1] == '-' && (s1[i+2] >= '0' && s1[i+2] <= '9') && s1[i+2] - s1[i] > 1) {
        append_range(s1[i], s1[i+2], s2, j);
        j += (1 + s1[i+2] - s1[i]);
        i += 2;
        continue;
      }
    }
    s2[j++] = s1[i];
  }
  s2[j] = '\0';
}

void append_range(char a, char b, char *s, int index) {
  for(; a <= b; a++)
    s[index++] = a;
}
