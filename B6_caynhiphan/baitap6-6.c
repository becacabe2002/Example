#include "../cgen/cgen.ic"
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main() {
    bn_tree_t tree = bns_create_tree_g(NULL, gtype_cmp_i);
    srand(time(NULL));
    char check;
    printf("Choose mode step(s) or final(f): ");
    scanf("%c", &check);
    if (check == 's')
        for (int i = 1; i <= 1000000; i++) {
            bns_insert_g(tree, gtype_i(rand() % 1000000));
            if (i % 10000 == 0) {
                printf("%d\n", i);
                printf("Real height: %ld\n", bn_edge_height(tree));
                printf("Optimal height: %ld\n", 1 + (long) log2(i));
                printf("Left height: %ld\n", bn_distance(bn_left_most(tree->root)));
                printf("Right height: %ld\n", bn_distance(bn_right_most(tree->root)));
                clear_stdin();
            }
        }
    else if (check == 'f') {
        for (int i = 1; i <= 1000000; i++)
            bns_insert_g(tree, gtype_i(rand() % 1000000));
        printf("Real height: %ld\n", bn_edge_height(tree));
        printf("Optimal height: %ld\n", 1 + (long) log2(1000000));
        printf("Left height: %ld\n", bn_distance(bn_left_most(tree->root)));
        printf("Right height: %ld\n", bn_distance(bn_right_most(tree->root)));
    }
    bn_free_tree(&tree);
    return 0;
}