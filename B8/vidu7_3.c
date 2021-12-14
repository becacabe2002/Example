#include "cgen.ic"

void selsort(int *a, const int n){
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; ++j){
			if(a[i] > a[j]){
				int tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int cmp_inc_i(const void *v1, const void *v2){
	return *((const int *)v1) - *((const int *)v2);
}

int main(int argc, char argv[]){
	if(argc != 2){
		printf("Usage: ./prog 10000\n");
		return 1;
	}
	int n;
	sscanf(argv[1], "%d", &n);
	if(n <0){
		printf("So luong phan tu = %d\n", n);
		return 1;
	}
	srand(time(NULL));
	int *a = malloc(n * sizeof(int)),
		*b = malloc(n*sizeof(int));
	for(int i = 0; i<n; i++){
		a[i] = b[i] = rand();
	}
	BENCH("Sap xep chon", 1, selsort(a, n));
	BENCH("Sap xep nh")
	return 0;
}