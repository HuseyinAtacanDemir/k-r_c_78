#include <stdio.h>

char * f_gets(char *s, int n, register FILE *iop)
{
  register int c;
  register char *cs;

  cs = s;

  while (--n > 0 && (c = getc(iop)) != EOF)
    if ((*cs++ = c) == '\n')
      break;
  *cs = '\0';
  return ((c == EOF && cs == s) ? NULL : s);
}

void f_puts(register char *s, register FILE *iop)
{
  register int c;
  
  while ((c = *s++))
    putc(c, iop);
}
