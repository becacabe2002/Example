#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    char nhapvao[1000];
    char canthay, thay;
    printf("Nhap day so: ");
    scanf("%[^\n]s", nhapvao);
    char *ptrthay = nhapvao;
    fflush(stdin);
    printf("Nhap chu muon thay: ");
    scanf("%c", &canthay);
    fflush(stdin);
    printf("Nhap chu thay the: ");
    scanf("%c", &thay);
    fflush(stdin);
    for(int i = 0; i < strlen(nhapvao); i++){
        if(*ptrthay == canthay) *ptrthay = thay;
        ptrthay++;
    }
    printf("%s", nhapvao);
    return 0;
}