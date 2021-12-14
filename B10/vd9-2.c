#include <stdio.h>

// tìm kiếm trong khoảng nửa mở l <= i < r
// trả về 1 nếu tìm thấy q, và trả về 0 nếu ngược lại
// 0 1 2 3 4 5 6 7 8 9
int binsearch(int l, int r, int *a, int q) {
  if (l >= r) {
    return 0;
  }
  int i = (l + r) / 2;
  if (a[i] > q) {
    return binsearch(l, i, a, q);
  } else if (a[i] < q) {
    return binsearch(i + 1, r, a, q);
  }
  return 1;
}

int main() {
  int a[] = {10, 20, 30, 50, 60, 70, 80,
            90, 100, 110, 120};
  int n = sizeof(a)/sizeof(a[0]);
  printf("%d\n", binsearch(0, n, a, 30));  // 1
  printf("%d\n", binsearch(0, n, a, 50));  // 1
  printf("%d\n", binsearch(0, n, a, 35));  // 0
  printf("%d\n", binsearch(0, n, a, 1));  // 0
  printf("%d\n", binsearch(0, n, a, 130));  // 0
  printf("%d\n", binsearch(0, n, a, 110));  // 1
  return 0;
}