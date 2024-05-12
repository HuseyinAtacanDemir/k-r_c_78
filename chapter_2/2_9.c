#include <stdio.h>

int bitcount(unsigned n);

main(){
  unsigned a = 0x88888888; // 8
  unsigned b = 0xAAAAAAAA; // 16
  unsigned c = 0xEEEEEEEE; // 24
  unsigned d = 0xFFFFFFFF; // 32

  printf("val: 0x%X, Bit Count: %d\n", a, bitcount(a));
  printf("val: 0x%X, Bit Count: %d\n", b, bitcount(b));
  printf("val: 0x%X, Bit Count: %d\n", c, bitcount(c));
  printf("val: 0x%X, Bit Count: %d\n", d, bitcount(d));
}

int bitcount(unsigned n) 
{
  int c;
  for (c = 0; n != 0; n &= n-1)
    c++;
  return c;
}
