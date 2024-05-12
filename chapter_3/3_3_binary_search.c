int binary(int x, int v[], int n);

main (){}

int binary(int x, int v[], int n) {
  int lo, hi, mid;

  low = 0;
  hi = n - 1;

  while (lo <= hi) {
    mid = (lo+hi)/2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      lo = mid + 1;
    else
      return mid;
  }
  return -1
}
