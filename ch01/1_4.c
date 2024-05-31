#include <stdio.h>

#define LOWER 0 /* lower limit of the table */
#define UPPER 150 /* upper limit */
#define STEP 5 /* step size */

main()
{
  int fahr;
  printf("F to C table with #define statements\n");
  printf("  f  |  c\n");
  for(fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
    printf("%4d %6.1f\n", fahr, (5.0/9.0)*(fahr-32.0));
}
