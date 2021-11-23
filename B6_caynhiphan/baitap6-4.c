#include "../cgen/ext/io.h"
#include "../cgen/cgen.ic"

gtype *bns_keys(bn_tree_t t, long *n) {
    *n = bn_size(t) ;
    gtype *a = malloc(*n * sizeof(gtype));
    int i = 0;
    bn_traverse_lnr(cur, t) {
        a[i] = to_bns_node_g(cur)->key;
        i++;
    }
    return a;
}

int main() {
    bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_i);
    bns_insert_g(t, gtype_i(4));
    bns_insert_g(t, gtype_i(2));
    bns_insert_g(t, gtype_i(3));
    bns_insert_g(t, gtype_i(1));
    bns_insert_g(t, gtype_i(5));
    bns_insert_g(t, gtype_i(6));
    bns_pprint(t, gtype_print_i);

    long n;
    gtype *a = bns_keys(t, &n);

    for (int i = 0; i < n; i++) {
        printf("%ld ", a[i].i);
    }
    printf("\n");
    free(a);
    bn_free_tree(&t);
    return 0;
}