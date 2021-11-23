#include <stdio.h>

int main(int argc, char * argv[]){
    int n;
    FILE *inp = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    int c = -20;
    while((c = fgetc(inp)) != EOF){
        fputc(c + n, out);
        c = fgetc(inp);
    }

    fclose(inp); fclose(out);
    return 0;
}