#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _so{
    int phannguyen;
    float phanthapphan;
};
typedef struct _so so;
so * split(float m, so * nhap){
    nhap->phannguyen = (int) m;
    nhap->phanthapphan = m - nhap->phannguyen;
    return nhap;
}
int main(void){
    float m;
    printf("Nhap so vao: ");
    scanf("%f", &m);
    so *ptr = (so*)malloc(sizeof(so));
    ptr = split(m, ptr);
    printf("Phan thap phan: %f\nPhan nguyen: %d", ptr->phanthapphan, ptr->phannguyen);
    return 0;
}