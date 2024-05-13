#include <stdio.h>

void shell_sort(int v[], int n);

main()
{
  int in[10] = {9,8,7,6,5,4,3,2,1,0};

  shell_sort(in, 10);
  int i;
  for(i = 0; i < 10; i++)
    printf("%d, ", in[i]);
  printf("\n");
}

void shell_sort(int v[], int n)
{
  int gap, i, j, temp;
  
  for (gap = n/2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
      for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
        temp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = temp;
      }
}
