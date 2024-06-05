#include <stdio.h>

/*
In c there is a strong relationship between pointers and arrays,
strong enough that pointers and arrays should be treated simultaneously.

Any op that can be achieved by array subscripting can also be done with ptrs.

*/
int str_len(char *s);

main()
{
  int a[10];

  int *pa;

  //following pairs of lines are equivalent
  pa = &a[0];
  pa = a;

  pa = &a[1];
  pa = a+1;

  int x = *pa; // set x to a[1]

  x = *(pa + 1); //set x to a[1 + 1]
  x = pa[1]; //same as above

  //&a[i] and a+i are identical.  
  //a[i] and *(a+i) are identical

  /*
  array names are constants
  so 
  a=pa
  a++
  p = &a
  are illegal
  */
  char *s = "test string";
  printf("Len of %s is %d", s, str_len(s));
}

int str_len(char *s)
{
  //incrementing s is legal since s is just a provate copy of the beginning address of the passed in string
  int n;
  for (n = 0; *s != '\0'; s++)
    n++;
  return n;
}
