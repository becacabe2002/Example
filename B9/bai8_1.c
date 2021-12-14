/* LẤY TOP K LỚN NHẤT
Cho tệp văn bản inp.txt chứa n số thực, với mỗi giá trị được ngăn 
cách bởi một khoảng trắng.
10 <= n <= 10^7

Yêu cầu: Chương trình yêu cầu người dùng nhập số K
 	Sau đó:
	1) Lặp tìm max K lần
	2) Sắp xếp rồi lấy top K
	3) Sử dụng Heap/hàng đợi ưu tiên với giới hạn K phần tử 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define to_double(p)  (*((const double*)p))
int cmp_inc_d(const void *a, const void *b){
	return to_double(a) - to_double(b);
}
int compare_d(const void *a, const void *b){
	if(to_double(a) - to_double(b) >0) return 1;
	else if(to_double(a) - to_double(b) == 0) return 0;
	else return -1;
}

int main(int argv, char * argc[]){
	if(argv != 2){
		printf("Usage: ./prog inp.txt");
		return 1;
	}
	FILE *f = fopen(argc[1], "r");
	if(!f){
		printf("Error while opening file.\n");
		return 1;
	}
	int K;
	int i = 0;
	printf("Please type K: ");
	scanf("%d", &K);
	fflush(stdin);
	double *list =(double*)malloc(1000*sizeof(double));
	while(!feof(f)){
		fscanf(f, "%lf", &list[i]);
		//printf("%lf\n", list[i]);
		i++;
	}
	qsort(list, 1000, sizeof(double), cmp_inc_d);
	for(int m = 0; m < K; m++) {
		printf("%lf\n", list[m]);
	}
	
	free(list);
	fclose(f);
	return 0;
}

