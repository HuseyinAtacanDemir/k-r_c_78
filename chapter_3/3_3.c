#include <stdio.h>
#include <string.h>
 
void itoa(int n, char *s);
void reverse(char *s);
main(){
  int a = 1 << 31;
  char s[30];

  itoa(a, s);
  printf("\n%d\n%s\n", a, s);
}


/*
Original version found below did not work because you cannot just multiply the smallest negative number with 
-1 and expect to get the positive counterpart.
Two's complement system uses n bits for negative and n-1 bits for positive numbers.
Thus we gotta change the algorithm so that we do not rely on taking hte absolute value of the input number
but we are actually handling negative numbers properly
so the loop condition should be changed and the modulo loguc should be changed
itoa(n, s) 
char s[];
int n;
{
    int i, sign;

    if ((sign = n) < 0)   
        n = -n;              
    i = 0;
    do {    
        s[i++] = n % 10 + '0';     
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
*/
void itoa(int n, char *s)    /* convert n to characters in s */
{
    int i, sign;
    sign = n;
    i = 0;
    do {    /* generate digits in reverse order */
        s[i++] = (sign >= 0) ? (n % 10 + '0') : -(n % 10) + '0';     /* get next digit */
    } while ((n /= 10) != 0); /* delete it */
    
  if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char *s)
{
  int i, j;
  for (i = 0, j = strlen(s)-1; j >= i; i++, j--) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
}
