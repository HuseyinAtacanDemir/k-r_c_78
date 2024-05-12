#include <stdio.h>

unsigned invert(unsigned x, unsigned p, unsigned n);

main () {
  unsigned test = 0xFFFFFFFF;

  /*Expected 0xFFFFFF07*/
  printf("val: 0x%X inverted: 0x%X\n", test, invert(test, 3, 5));
}

unsigned invert(unsigned x, unsigned p, unsigned n) {
  return x ^ (~(~0 << n) << p);
}
