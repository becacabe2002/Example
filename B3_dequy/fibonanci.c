#include <stdio.h>

int main(void){
	int n1 = 0;
	int n2 = 1;
	int result;
	int so;
	printf("Hay nhap so can tim: ");
	scanf("%d", &so);
	for(int i = 0;  i <so; i++){
		result = n1 + n2;
		int tmp = n1;
		n1 = n2;
		n2 = n2 +tmp;
	}
	printf("Ket qua = %d\n", result);
	return 0;
}