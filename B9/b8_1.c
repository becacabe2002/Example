#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define to_d(x) (*(const double *)x)
int compare_d(const void *a, const void *b){
    return to_d(b) - to_d(a);
}
int main(){
    FILE *f = fopen("inp.txt","r");
    double d[1000];
    int k;
    scanf("%d",&k);
    int i = 0;
    while(!feof(f)){
        fscanf(f,"%lf",&d[i]);
        i++;
    }
    clock_t start = clock();
    qsort(d,1000,sizeof(double),compare_d);
    for(int i=0; i<k; i++){
        printf("%lf ",d[i]);
    }
    fclose(f);
    clock_t end = clock();
    double time_process = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThoi gian: %lf",time_process);
    return 0;
}