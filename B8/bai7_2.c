#include "cgen.h"
#include "ext/io.h"

#include <stdio.h>
#include <string.h>

typedef char* pchar;
#define to_s(p) (*(const char*)p)
int cmp_inc_s(const void *s1, const void *s2){
	printf("%s %s\n", to_s(s1), to_s(s2));
	return strcmp(to_s(s1), to_s(s2));
}

int main(){
	char ** a;
	int n = 0;
	printf("n = ");
	scanf("%d", &n);
	a = malloc(n * sizeof(pchar));
	printf("Nhap chuoi ky tu:\n");
	pchar s;
	clear_stdin();
	for(int i = 0; i<n; i++){
		if(cgetline(&s, 0, stdin)){
			remove_tail_lf(s);
			a[i] = strdup(s);
		}
	}
	free(s);
	//a[i] co kieu char*
	// cmp_inc_s nhan dia chi cua a[i]
	// a co kieu dung phai la char**
	qsort(a, n, sizeof(a[n]), cmp_inc_s);
	printf("Sau khi sap xep:\n");
	for(int i = 0; i < n; i++){
		printf("a[%d] = %s\n", i, a[i]);
	}
	for(int i = 0; i<n; i++){
		free(a[i]);
	}
	free(a);
	return 0;
}