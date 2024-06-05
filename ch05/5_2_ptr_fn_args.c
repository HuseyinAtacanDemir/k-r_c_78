#include <stdio.h>
#include <stdlib.h>

#define ASC 1
#define DESC 0

#define CALL_BY_VALUE 1
#define PTR 0

void swap(int x, int y);
void swap_ptr(int *px, int *py);
void unified_swap(int swap_mode, int a, int b, int *c, int *d);
void selection_sort(int arr[], int len, int order, int swap_mode, void (*swap)(int, int, int , int*, int*));
void print_arr(int arr[], int len);

main()
{
  int len = 10;
  int arr[len];
  int i;
  for (i = 0; i < len; i++)
    arr[i] = (rand() % 100) + 1;
  
  print_arr(arr, len);

  selection_sort(arr, len, ASC, CALL_BY_VALUE, unified_swap);

  print_arr(arr, len);

  selection_sort(arr, len, ASC, PTR, unified_swap);

  print_arr(arr, len);

  selection_sort(arr, len, DESC, PTR, unified_swap);

  print_arr(arr, len);
}

void print_arr(int arr[], int len)
{
  int i;
  printf("Contents of Arr:\n");
  for (i = 0; i < len; i++)
    printf(" %d,", arr[i]);
  printf("\n");
}

/*
Since C passes args to fns by "call by value",
there is no direct way for the called fn to alter
a var in the calling fn.

Ex: a sorting routine might exchange two
out of order elements with a fn called swap.

*/

// Not enough to write this, since the elements in the calling routine cannot be affected
void swap(int x, int y)
{
  int temp;
  
  temp = x;
  x = y;
  y = temp;
}

void swap_ptr(int *px, int *py)
{
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}

void unified_swap(int swap_mode, int a, int b, int *c, int *d)
{
  if (swap_mode == CALL_BY_VALUE)
    swap(a, b);
  else if (swap_mode == PTR)
    swap_ptr(c, d);
}

void selection_sort(int arr[], int len, int order, int swap_mode, void (*swap)(int, int, int, int*, int*))
{
  int i, j, swap_index;
  for (i = 0; i < len-1; i++) {
    swap_index = i;
    for (j = i+1; j < len; j++)
      if (arr[swap_index] > arr[j] && order == ASC)
        swap_index = j;
      else if (arr[swap_index] < arr[j] && order == DESC)
        swap_index = j;

    if (swap_index != i)
      (*swap)(swap_mode, arr[swap_index], arr[i], &arr[swap_index], &arr[i]);
  }   
}
