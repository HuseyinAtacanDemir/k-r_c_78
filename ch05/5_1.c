#include <stdio.h>

main()
{
  int x, y;
  int *px, *py;

  //px is the address of x
  px = &x;

  //set x to 1
  x = 1;

  //set content of the adress at px to 0
  *px = 0;

  printf("Set x to 1, but then set *px to 0:\nx: %d, *px: %d\n\n", x, *px); 

  //same as y = x
  y = *px;

  printf("Set y = *px\ny = %d\n\n", y); 

  //y = x + 1
  y = *px + 1;

  printf("Set y = *px + 1\ny = %d\n\n", y);

  //x++
  (*px)++;
  
  printf("(*px)++\nx: %d\n\n", x);

  //x += 2
  *px += 2;

  printf("Set *px += 2\n%d\n\n", *px);

  //since pointers are variables, they can be manipulated like variables
  //make py point to the same place px is pointing at
  py = px;

  printf("Set py = px\n*py: %d, *px: %d\n\n", *py, *px);
  
  printf("py: %p, px: %p\n", py, px);
}
