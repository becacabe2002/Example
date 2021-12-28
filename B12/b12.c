#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "io.h"

typedef struct product_s{
	char *name;
	char *code;
	long price;
	int number;
} *product_t;


int main(){
  FILE *fp =fopen("inp.txt", "r");
  if(!fp){
  	printf("\nKhong the mo tep\n");
  	return 1;
  }
  	char buff[512];

	fgets(buff, sizeof(buff), fp);
	buff[strcspn(buff, "\n")] = 0;
	size_t n;

	sscanf(buff, "%zu", &n);

  product_t *danh_sach = (product_t*)calloc(n, sizeof(product_t));
  // chưa cấp phát bộ nhớ. danh_sach[i] mới là 1 con trỏ, cần cấp phát bộ nhớ mới có thể truy cập vào phần tử
  for(int i=0;i<n;i++){
    danh_sach[i] = (product_t)calloc(1,sizeof(struct product_s));
//    danh_sach[i]->code = (char*)malloc(1024*sizeof(char));
//    danh_sach[i]->name = (char*)malloc(1024*sizeof(char));
  }
  // đã cấp phát bộ nhớ
  unsigned int so_hang = 0;
  char *lineptr = NULL; // NULL pointer?
  while(!feof(fp)){ // for loop???
  	lineptr = cgetline(&lineptr, 0, fp);
  	lineptr = remove_tail_lf(lineptr);
  	danh_sach[so_hang]->code = strtok(lineptr," ");
  	danh_sach[so_hang]->name = strtok(NULL, " ");
  	danh_sach[so_hang]->price = atoi(strtok(NULL, " "));
  	danh_sach[so_hang]->number = atoi(strtok(NULL, " "));
  	so_hang++;
  }
  fclose(fp);
  // check imported information
  for(int i=0;i<n;i++){
    printf("%d:%s\n%s\n%ld\n%d\n",i+1,danh_sach[i]->code,danh_sach[i]->name,danh_sach[i]->price,danh_sach[i]->number);
  }
  // main program
for(;;){
	int choice;
	printf("\n----->Cong ty Ngo Minh Tu<----\n");
	printf("1. Xem thong tin\n");
	printf("2. Tao don hang\n");
	printf("3. Thoat chuong trinh\n");
	printf("Lua chon cua quy khach (1-3):");
	scanf("%d", &choice);
	getchar(); // remove newline char
	if(choice>3 || choice <1){
		printf("Lua chon khong hop le. Xin vui long chon lai\n");
		continue;
	}
	if(choice == 1){
//		char *find_code = NULL; // NULL pointer?
        char find_code[100];
		printf("\nNhap ma so mat hang muon xem");
//		find_code = cgetline(&find_code, 0, stdin);
//		find_code = remove_tail_lf(find_code);
        scanf("%s",find_code);
		for(int i = 0; i< so_hang;){ // <= ?????
			if(i > so_hang){
				printf("\n Khong tim duoc san pham\n");
				break;
			}
			if(strcmp(danh_sach[i]->code, find_code) == 0){
				printf("\n Ten san pham: %s", danh_sach[i]->name);
				printf("\n So luong san pham con lai: %d", danh_sach[i]->number);
				printf("\n Don gia san pham: %ld", danh_sach[i]->price);
				break;
			}
			else{
				i++;
			}
		}
		free(find_code);
	}
	else if(choice == 2){
		int giohang[10][2];
		int m = 0;
		for(;;){
		int so_luong;
		char *find_code;
		printf("\nMoi quy khach chon hang:\nNhap ma:");
		find_code = cgetline(&find_code, 0, stdin);
		find_code = remove_tail_lf(find_code);
		for(int i = 0; i< so_hang; i++){ // <=
			if(strcmp(danh_sach[i]->code, find_code) == 0){
				printf("\nMoi quy khach chon so luong:");
				scanf("%d", &so_luong);
					for(;;){
					if(danh_sach[i]->number < so_luong){
					printf("\nSo luong vuot qua so luong ton kho. Vui long chon lai:");
					printf("\nMoi quy khach chon so luong:");
					scanf("%d", &so_luong);
				} else break;
				}
			giohang[m][0] = i;
			giohang[m][1] = so_luong;
			m++;
			} else continue;
		}
	}
	long sum = 0;
	for(int j = 0; j <= m; j++){
		printf("\nHoa don mua hang\n");
		printf("%d.\t%s\t%dx%ld\n", j+1, danh_sach[giohang[j][0]]->name,
			giohang[j][1], danh_sach[giohang[j][0]]->price);
		sum += danh_sach[giohang[j][0]]->price*giohang[j][1];
	}
	printf("Tong gia tri don hang = %ld", sum);
	}
	else if(choice == 3){
        free(danh_sach);
        return 0;
	}
}
}

