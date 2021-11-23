#include <stdio.h>
#include "cgen.ic"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ./wu story.txt\n");
        return 1;
}
    FILE *in = fopen(argv[1], "r");
    if(!in) {printf("Error while opening file %s", argv[1]);
    return 1;
}
char buff[100][100];
bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_s);
int wordnum = 0;
int i = 0;
while (fscanf(in, "%s", buff[i]) != EOF){
    if(!bns_search_g(t, gtype_s(buff[i]))){
        wordnum++;
        bns_insert_g(t, gtype_s(buff[i]));
    }
    i++;
    }
    bns_pprint(t,gtype_print_s);
    printf("So tu: %d\n", wordnum);
    printf("Danh sach cac tu duy nhat:\n");
    bn_traverse_lnr(cur, t){
        printf("%s\t", bns_node_g_key(cur).s);
    }
    printf("\n");
    fclose(in);
    return 0;
}

