#include <stdio.h>

int ketqua[100][100] = {0};

int C(int k, int n ){
	if(ketqua[k][n] != 0) return ketqua[k][n];
	else if(k == 0 || k == n){
		ketqua[k][n] = 1;
		return 1;
	}
	ketqua[k][n] = C(k-1,n) + C(k-1,n-1);
	return ketqua[k][n];
}

int main(void){
	int a,b;
	printf("Nhap to hop can tim: ");
	scanf("%d %d", &a, &b);
	printf("To hop chap %d cua %d = %d", a, b, C(a,b));

	return 0;
}