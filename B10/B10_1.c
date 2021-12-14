/*
Đề bài: Cho dãy n số nguyên trong tệp văn bản (không trùng lặp) inp.txt
	    theo định dạng: 
	inp.txt
	5
	1 2 3 5 6

Hãy viết chương trình nhận 1 số nguyên Q qua tham số dòng lệnh, 
sau đó đếm bộ số (i,j) sao cho 0<= i,j <= n và a_i + a_j = 0

	* Cài đặt thuật toán vét cạn
	* Cài đặt thuật toán cải tiến, sử dụng tìm kiếm nhị phân
	* So sánh về thời gian thực hiện các giải thuật

1. Đọc tệp và lưu mảng
2. Tìm kiếm nhị phân
3. Giải quyết bài toán bằng vét cạn. - tự cài
4. Giải quyết bài toán bằng tìm kiếm nhị phân.  // ví dụ tk nhị phân
	+ Sắp xếp mảng đầu vào theo thứ tự tăng dần;
	+ for (i = 0; i < n-1; i++)
	+ cần tìm j>i sao cho a[j] + a[i] = q
		binsearch(i+1, n, a, q-a[i])
	=> thời gian sắp xếp: n * log(n) + n.log(n) = n.log(n)
5. Tái cấu trúc & so sánh 2 giải pháp theo thời gian xử lý. // tự cài

*/

/*-----Ví dụ về tìm kiếm nhị phân -------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare_i(const void *a, const void *b){
	return (*(int*)a - *(int*)b);
}

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
void vetcan(int *a, int length, int Q){
	int socap = 0;
	for(int i = 0; i <= length-2;i++){
		for(int j = i+1; j <= length-1;j++){
			if(*(a+i) + *(a+j) == Q ){
				//printf(" %d + %d = %d\n", *(a+i), *(a+j), Q);
				socap++;
			}
		}
	}
	socap = socap;
	printf("So cap: %d\n", socap);
}

void tknhiphan(int *a, int length, int Q){
	int socap = 0;
	for(int i = 0; i < length-1;i++){
		if(binsearch(i, length, a, Q - *(a+i)) == 1) socap++;
		else continue;
	}
	printf("So cap: %d\n", socap);
}

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Usage: ./prog inp.txt 10\n");
		return 0;
	}
	int q;
	sscanf(argv[2], "%d", &q);
	FILE *f = fopen(argv[1], "r");
	int n;
	fscanf(f, "%d", &n);
	int *a = malloc(sizeof(int)*n);
	for(int i = 0; i<n; ++i){
		fscanf(f, "%d", a + i);
	}
	fclose(f);
	clock_t t1 = clock();
	vetcan(a, n, q);
	clock_t t2 = clock();
	qsort(a, n, sizeof(int), compare_i);
	tknhiphan(a, n, q);
	clock_t t3 = clock();
	printf("Thoi gian chay vet can: %lfs\nThoi gian chay tim kiem nhi phan: %lfs", 
			(double)(t2 - t1)/CLOCKS_PER_SEC, (double)(t3 - t2)/CLOCKS_PER_SEC);
	return 0;
}
