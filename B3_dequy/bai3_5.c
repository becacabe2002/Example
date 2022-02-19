#include <stdio.h>

#define N 100
int x[N], k, n;

void output() {
    for (int i = 0; i < k; ++i) {
        printf("%d ", x[i]);
    }
    printf("\n");
}
/*
 k = 2, v[0],v[1]  -- n = 3, -- 1, 2, 3
 v[0] = 1, 2
 */
void try(int i) {
    int v = i > 0? x[i - 1] + 1 : 1;
    for (; v <= n - k + i + 1; ++v) {
        x[i] = v;
        if (i == k - 1) {
            // kiem tra
            output();
        } else {
            try(i + 1);
        }
    }
}

int main() {
    printf("Nhap k, n = ");
    scanf("%d%d", &k, &n);
    try(0);
    return 0;
}