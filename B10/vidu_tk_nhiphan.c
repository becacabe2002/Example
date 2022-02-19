#include <stdio.h>

// tìm kiếm trong khoảng nửa mở l <= i<r
// trả về l nếu tìm thấy q, trả về 0 nếu ngược lại

int binsearch(int l, int r, int* a, int q){
	if(l>= r) return 0;
	int i = (l+r)/2;
	if(a[i] > q){
		return binsearch(l, i, a, q);
	}
	else if(a[i] < q){
		return binsearch(i+1,r, a, q);
	}
	return 1;
}

int main(){
	int a[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130};
	int n = sizeof(a)/sizeof(a[0]);
	printf("%d\n", binsearch(0, n, a, 10));
	printf("%d\n", binsearch(0, n, a, 20));
	printf("%d\n", binsearch(0, n, a, 70));
	printf("%d\n", binsearch(0, n, a, 80));
	printf("%d\n", binsearch(0, n, a, 100));
	printf("%d\n", binsearch(0, n, a, 130));
	return 0;
}