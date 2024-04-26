#include <stdio.h>

/* print Fahrenheir-Celsius table
for f = -30, -25, ..., 120 */

main()
{
  int lower, upper, step;
  float fahr, celsius;
  lower = -30;
  upper = 120;
  step = 5;
  fahr = lower;

  printf("  f  |  c  \n");
  while (fahr <= upper) {
    celsius = (5.0/9.0) * (fahr-32.0);
    printf("%4.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }

  upper = 60;
  step = 3;
  celsius = lower;
  printf("  c  |  f  \n");
  while (celsius <= upper) {
    fahr = ((9.0/5.0) * celsius) + 32.0;
    printf("%4.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
  
}
