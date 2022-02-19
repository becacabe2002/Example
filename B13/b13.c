#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct hang_s{
	char code[100];
	int price;
}hang;

typedef struct order_s{
	char name[100];
	int number;
	int money;
}order;

#define ordertonumber(a) (*(order*)a).money
int cmpfunc(const void *a, const void *b){
	if(ordertonumber(a) > ordertonumber(b)) return -1;
	if(ordertonumber(a) < ordertonumber(b)) return 1;
	if(ordertonumber(a) = ordertonumber(b)) return 0;
}

#define ptrtohang(a) (*(hang*)a).price
int cmpfunc2(const void *a, const void *b){
	if(ptrtohang(a) > ptrtohang(b)) return -1;
	if(ptrtohang(a) < ptrtohang(b)) return 1;
	if(ptrtohang(a) = ptrtohang(b)) return 0;
}


int main(int argc, char *argv[]){
	int sl1, sl2;
	clock_t begin = clock();
	if(argc != 3){
		printf("Usage: ./prog products.txt orders.txt.\n");
		return 0;
	}
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "r");
	if(fp1 == NULL || fp2 == NULL){
		printf("Error while opening files.");
		return 0;
	}
	fscanf(fp1, "%d", &sl1);
	fscanf(fp2, "%d", &sl2);
	hang *danhsach =malloc(sl1 * sizeof(struct hang_s));
	for(int i = 0; i < sl1-1; i++){
		fscanf(fp1,"%s", danhsach[i].code);
		fscanf(fp1,"%d", &danhsach[i].price);
		//printf("Price of %s is %d\n", danhsach[i].code, danhsach[i].price);
	}
	fclose(fp1);
	qsort(danhsach, sl1, sizeof(hang), cmpfunc2);
	//printf("\n%s\n",danhsach[sl1/2].code);
	order *list = malloc(sl2 *sizeof(struct order_s));
	for(int i = 0; i <sl2; i++){
		list[i].money = 0;
		fscanf(fp2, "%s", list[i].name);
		fscanf(fp2, "%d", &list[i].number);
		for(int j = 0; j <list[i].number; j++){
			char temp[100];
			int tempnum;
			fscanf(fp2, "%s", temp);
			fscanf(fp2, "%d", &tempnum);
			for(int m = 0; m <sl1-1; m++){
				if(strcmp(temp, danhsach[m].code) == 0){
					list[i].money += danhsach[m].price * tempnum;
				}
			}
		}
		//printf("%s\t%d\n", list[i].name, list[i].money);
	}
	fclose(fp2);
	qsort(list, sl2, sizeof(order), cmpfunc);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	for(int i = 0; i<3;i++){
		printf("%s %d\n", list[i].name, list[i].money);
	}
	printf("Runtime: %lf\n", time_spent);
	return 0;
}