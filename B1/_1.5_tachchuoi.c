#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
    char luu[100][100];
    char nhapvao[1000];
    int sochu = 0;
    printf("Nhap chuoi ky tu: ");
    scanf("%[^\n]s", nhapvao);
    char *ptr = nhapvao;
    for(int i = 0; i <= strlen(nhapvao)-1; i++){
        if(isalpha(*ptr) != 0){
            int n = 0;
            while(isalpha(*ptr) != 0){
                luu[sochu][n] = *ptr;
                n++;
                ptr++;
            }
            luu[sochu][n] = '\0';
            sochu++;
        }
        ptr++;
    }
    for(int i = sochu -1; i >= 0; i--){
    printf("\n%s\n", luu[i]);
    }
    return 0;
}