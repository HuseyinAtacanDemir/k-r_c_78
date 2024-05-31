#include <stdio.h>

/*Get the bits of X starting from position p to p+n*/
unsigned getLeftBits(unsigned x, unsigned p, unsigned n);
/*Get the bits of X starting from position p to p-n*/
unsigned getRightBits(unsigned x, unsigned p, unsigned n);

main () {
  unsigned ex1 = 0xCC;
  unsigned ex2 = 0x77;

  /* Expected: 0x3*/
  printf("0x%x\n", getRightBits(ex1, 3, 2)); 
  /* Expected: 0x19*/
  printf("0x%x\n", getLeftBits(ex1, 3, 5)); 

}

unsigned getRightBits(unsigned x, unsigned p, unsigned n){
  return (x >> (p+1-n)) & ~(~0 << n);
}
unsigned getLeftBits(unsigned x, unsigned p, unsigned n){
  return (x >> p & ~(~0 << n));
}


