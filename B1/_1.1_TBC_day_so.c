#include <stdio.h>

int main(){
    int so;
    float TB;
    int tong = 0;
    int day[100];
    printf("Nhap so luong phan tu: ");
    scanf("%d", &so);
    fflush(stdin);
    printf("Nhap day so: \n");
    for(int i = 0; i<= so -1; i++){
        scanf("%d", &day[i]);
        tong += day[i];
        fflush(stdin);
    }
    TB = tong/so;
    printf("\n%.2f\n", TB);
    for(int i = 0; i <= so-1;){
        if(TB>=day[i+1]) i++;
        else{
            printf("day[%d] = %d\n", i+1, day[i+1]);
            printf("day[%d] = %d\n", i, day[i]);
            break;
        }
    }
return 0;
}