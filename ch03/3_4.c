#include <stdio.h>
#include <string.h>
 
void itob(int n, char *s);
void itoh(int n, char *s);
main(){
  int a = 134558458;
  char s[35];
  char s1[11];

  itob(a, s);
  itoh(a, s1);
  printf("\n%d\n%s\n%s\n", a, s, s1);
}

void itob(int n, char *s)    /* convert n to a binary representation string in s */
{
    unsigned mask = 1 << 31;
    unsigned input = (unsigned) n;
    int i = 2;
    s[0] = '0';
    s[1] = 'b';
    do { 
       s[i++] = (mask & input) != 0 ? '1' : '0';
    } while ((mask >>= 1) != 0);
    
    s[i] = '\0';
}

void itoh(int n, char *s)
{
  char sb[35];
  itob(n, sb);
  
  int i;
  int j = 2;
  s[0] = '0';
  s[1] = 'x';
  for (i = 0; i < 32; i += 4) {
    int digit = 
      ((sb[i+0] - '0') * 8) + 
      ((sb[i+1] - '0') * 4) +
      ((sb[i+2] - '0') * 2) +
      ((sb[i+3] - '0') * 1);
    switch(digit) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
        s[j++] = ('0' + digit);
        break;
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        s[j++] = 'A' + (digit - 10);
        break;
    }
  }
  s[j] = '\0';
}
