#include <stdio.h>
#include <string.h>
#define N 10

int main(){
    char buff[N];
    FILE * inp = fopen("lab1.txt", "r");
    while(fgets(buff, N, inp)){
        printf("%ld %s\n", strlen(buff), buff);
    }
    return 0;
}