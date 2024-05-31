#include <stdio.h>
#include <limits.h>

#define INT_BITS (sizeof (int) * CHAR_BIT)

unsigned rightrot(unsigned n, unsigned b);

main(){
  unsigned test1 = 0x55555555;
  printf("Value: 0x%X\n", rightrot(test1, 5));
}

unsigned rightrot(unsigned n, unsigned b) {
  unsigned nu = n;
  unsigned mask = ~(~0 << b);
  nu = nu >> b;
  nu = nu | ((n & mask) << (INT_BITS - b));
  return nu;
}
