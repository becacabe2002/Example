#include <stdio.h>
#include <stdlib.h>

#define to_double(p)  (*((const double*)p))
int cmp_inc_d(const void *a, const void *b){
	return to_double(a) - to_double(b);
}
void print_a(double *a, int n){
	for(int i = 0; i < n; i++){
		printf("%.1lf\t", *(a+i));
	}
}

int compare_d(const void *a, const void *b){
	if(to_double(a) - to_double(b) >0) return 1;
	else if(to_double(a) - to_double(b) == 0) return 0;
	else return -1;
}

int main(){
	int n;
	printf("Nhap so luong phan tu co trong mang: ");
	scanf("%d", &n);
	double *a=calloc(n, sizeof(double));
	printf("Nhap cac phan tuu trong mang: ");
	for(int i = 0; i < n; i++){
		scanf("%lf", &a[i]);
	}
	qsort(a, n, sizeof(a[0]), compare_d);
	printf("Mang sau khi sap xep: ");
	print_a(a, n);
	free(a);
	return 0;
}

