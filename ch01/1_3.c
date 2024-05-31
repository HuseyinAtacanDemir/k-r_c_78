#include <stdio.h>

main()
{

  int fahr;
  printf("  f  |  c \n");
  for (fahr = 0; fahr <= 150; fahr = fahr + 5)
    printf("%4d %6.1f\n", fahr, (5.0/9.0)*(fahr-32.0));

  printf("\n");
  printf("reverse order\n");
  printf("  f  |  c \n");
  for (fahr = 150; fahr >= 0; fahr = fahr - 5)
    printf("%4d %6.1f\n", fahr, (5.0/9.0)*(fahr-32.0));

}
