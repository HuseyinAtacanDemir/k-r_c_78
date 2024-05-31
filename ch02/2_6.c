#include <stdio.h>
#include <stdint.h>

main () {

  uintptr_t a = 0x1;
  uintptr_t max = ~0;
  int i;

  
  for (i = 1; i < 512; i++)
    if (a == (max >> i))
      break;
  
  printf("Word Length of host: %d\n", i+1);
}
