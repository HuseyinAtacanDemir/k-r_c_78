#include <stdio.h>
#include "7_2_helpers.h"

double val[MAXVAL];
int sp = 0;

double push(double f)
{
  if (sp < MAXVAL)
    return (val[sp++] = f);
  else {
    printf("Error: Stack Full\n");
    clear();
    return 0;
  }
} 

double pop()
{
  if (sp > 0)
    return (val[--sp]);
  else {
    printf("Error: Stack Empty\n");
    clear();
    return 0;
  }
}

void clear()
{
  sp = 0;
}
