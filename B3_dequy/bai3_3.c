#include <stdio.h>
/* Liệt kê dãy n bits không có 2 bits 0 liền nhau */

/* Kiểm tra xem có 2 bits 0 liền nhau trong dãy n hay không? */

/* Duyệt qua tất cả các dãy n bits */
    /* Nếu thỏa mãn điều kiện thì in ra */
// s(i) - 0 + s(i + 1)
//       1 + s(i + 1)
#define N 100
int x[N], n, k;

void output() {
    for (int i = 0; i < n; ++i) {
        printf("%d", x[i]);
    }
    printf("\n");
}

int count1() {
    int cc = 0;
    for (int i = 0; i < n; ++i) {
        cc += x[i];
    }
    return cc;
}

void try(int i) {
    for (int j = 0; j <= 1; ++j) {
        x[i] = j;
        if (i == n - 1) {
            if (count1() == k) {
                output();
            }
        } else {
            try(i + 1);
        }
    }
}

int main() {
    printf("Nhap n, k = ");
    scanf("%d%d", &n, &k);
    try(0);
    return 0;
}