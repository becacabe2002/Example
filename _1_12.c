#include <stdio.h>

int main(void){
    FILE * f1 = fopen("lab1.txt", "r");
    FILE * f2 = fopen("lab2.txt", "w");
    int c;
    c = fgetc(f1);
    while(!feof(f1)){
        fputc(c, f2);
        c = fgetc(f1);
    }
    fclose(f1);  fclose(f2);
    return 0;
}