#include <stdio.h>

int main(int argc, char *argv[]){
    FILE * input = fopen(argv[1], "r");
    if(argc != 3){
        printf("Usage: ./prog input.txt output.txt \n");
        return 1;
    }
    if(!input){
        printf("Loi mo tep %s\n", argv[1]);
        return 1;
    }
    FILE * output = fopen(argv[2], "w");
    if(!output){
        printf("Loi mo tep %s\n", argv[2]);
        return 1;
    }
    int c;
    while ((c = fgetc(input)) != EOF){
        fputc(c, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}