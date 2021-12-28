#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgen.ic"
#include "ext/io.h"

typedef struct song_s{
    char *name;
    char *singer;
    char *composer;
    int year;
} *song_t;

typedef struct sll_node_song_s{
    struct sll_node_s base;
    char *name;
    char *singer;
    char *composer;
    int year;
} *sll_node_song_t;

#define to_sll_node_song(n) ((sll_node_song_t)n)
#define sll_node_song_name(n) (to_sll_node_song(n)->name)
#define sll_node_song_singer(n) (to_sll_node_song(n)->singer)
#define sll_node_song_composer(n) (to_sll_node_song(n)->composer)
#define sll_node_song_year(n) (to_sll_node_song(n)->year)

int cmp_song_name(const void *a, const void *b){
    return strcmp((((song_t)a)->name), (((song_t)b)->name));
}

int cmp_song_singer(const void *a, const void *b){
    return strcmp((((song_t)a)->singer), (((song_t)b)->singer));
}

int cmp_song_composer(const void *a, const void *b){
    return strcmp((((song_t)a)->composer), (((song_t)b)->composer));
}

int cmp_song_year(const void *a, const void *b){
    return (((song_t)a)->year) - (((song_t)b)->year);
}

sll_node_t sll_create_node_song(const char *name, const char *singer,
                        const char *composer, int year){
    sll_node_t tmp = sll_create_node();
    sll_node_song_t nn = realloc(tmp, sizeof(struct sll_node_song_s));
    nn->name = strdup(name);
    nn->singer = strdup(singer);
    nn->composer = strdup(composer);
    nn->year = year;
    return (sll_node_t)(nn);
}

void sll_push_back_song(sll_t list, const char *name, 
                const char *singer, const char *composer, int year){
    sll_push_back(list, sll_create_node_song(name, singer, composer, year));          
}

void sll_pprint_node_song(sll_node_t node){
    printf("%s - %s - %s - %d", sll_node_song_name(node), sll_node_song_singer(node), 
                sll_node_song_composer(node), sll_node_song_year(node));
}

void sll_pprint_list_song(sll_t list){
    sll_traverse(cur, list){
        sll_pprint_node_song(cur);
        printf("\n");
    }
}

void delete_line_file(char *argv, char *str){
    char buff[100];
    char *x;
    int c = 0;
    FILE *f1 = fopen(argv, "r");
    FILE *f2 = fopen("tmp.txt", "w");
    while(feof(f1) == 0){
        fscanf(f1, " %[^\n]%*c", buff);
        x = strstr(buff, str);
        if(!x){
            if(c != 0){
                fprintf(f2, "\n");
            }
            fputs(buff, f2);
        }
        c++;
    }
    fclose(f1);
    fclose(f2);
    remove(argv);
    rename("tmp.txt", argv);
}

int main(int argc, char *argv[]){
    // == INPUT == //
    FILE *fi = fopen(argv[1], "a+");
    sll_t list = sll_create_list();
    char *line = (char*)malloc(100 * sizeof(char));
    char **inf = (char**)malloc(100 * sizeof(char*));
    while(cgetline(&line, 0, fi)){
        char *name, *singer, *composer;
        int year;
        char *token;
        token = strtok(line, "#*#");
        int i = 0;
        while(token != NULL){
            inf[i] = token;
            i++;
            token = strtok(NULL, "#*#");
        }
        name = inf[0];
        singer = inf[1];
        composer = inf[2];
        year = atoi(inf[3]);
        sll_push_back_song(list, name, singer, composer, year);
    }

    // == STORE DATA INTO ARRAY == //
    long sz = sll_length(list);
    song_t a = malloc(sizeof(struct song_s) * sz);
    long idx = 0;
    sll_traverse(cur, list){
        a[idx].name= sll_node_song_name(cur);
        a[idx].singer = sll_node_song_singer(cur);
        a[idx].composer = sll_node_song_composer(cur);
        a[idx].year = sll_node_song_year(cur);
        idx++;
    }
    fclose(fi);

    // == MENU == //
    int t;
    while(1){
        printf("====== LIST OF SONGS ======\n");
        sll_pprint_list_song(list);
        printf("***************************************");
        printf("\n\n");
        printf("====== MENU ======\n");
        printf("1. See list of songs by order\n");
        printf("2. Find songs\n");
        printf("3. Add a new song\n");
        printf("4. Remove song\n");
        printf("5. Quit\n");
        printf("Choose (1-5): ");
        scanf("%d", &t);
        fflush(stdin);

        if(t < 1 || t > 5){
            printf("Wrong input. Choose again.\n");
            continue;
        }
        else if(t == 1){
            while(1){
                char v;
                printf("List song in:\n");
                printf("a. Name order\n");
                printf("b. Singer order\n");
                printf("c. Composer order\n");
                printf("d. Year order\n");
                printf("e. Quit\n");
                printf("Choose (a-e): ");
                scanf(" %c", &v);
                fflush(stdin);

                if(v != 'a' && v != 'b' && v != 'c' && v != 'd' && v != 'e'){
                    printf("Wrong input. Choose again.\n");
                    continue;
                }
                else if(v == 'a'){
                    qsort(a, idx, sizeof(struct song_s), cmp_song_name);
                    for(long i = 0; i < idx; i++){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                else if(v == 'b'){
                    qsort(a, idx, sizeof(struct song_s), cmp_song_singer);
                    for(long i = 0; i < idx; i++){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                else if(v == 'c'){
                    qsort(a, idx, sizeof(struct song_s), cmp_song_composer);
                    for(long i = 0; i < idx; i++){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                else if(v == 'd'){
                    qsort(a, idx, sizeof(struct song_s), cmp_song_year);
                    for(long i = 0; i < idx; i++){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                else if(v == 'e'){
                    break;
                }
            }
        }
        else if(t == 2){
            char v;
            char s[100];
            int y;
            printf("Find by:\n");
            printf("a. Name\n");
            printf("b. Singer\n");
            printf("c. Composer\n");
            printf("d. Year\n");
            printf("e. Quit\n");
            printf("Choose (a-e):");
            scanf(" %c", &v);
            fflush(stdin);

            if(v != 'a' && v != 'b' && v != 'c' && v != 'd' && v != 'e'){
                printf("Wrong input. Choose again.\n");
                continue;
            }
            else if(v == 'a'){
                printf("Find name: ");
                scanf(" %[^\n]%*c", s);
                for(long i = 0; i < idx; i++){
                    if(strstr(a[i].name, s) != NULL){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                printf("\n");
            }
            else if(v == 'b'){
                printf("Find singer: ");
                scanf(" %[^\n]%*c", s);
                for(long i = 0; i < idx; i++){
                    if(strstr(a[i].singer, s) != NULL){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                printf("\n");
            }
            else if(v == 'c'){
                printf("Find composer: ");
                scanf(" %[^\n]%*c", s);
                fflush(stdin);
                for(long i = 0; i < idx; i++){
                    if(strstr(a[i].composer, s) != NULL){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                printf("\n");
            }
            else if(v == 'd'){
                printf("Find year: ");
                scanf(" %d", &y);
                fflush(stdin);
                for(long i = 0; i < idx; i++){
                    if(a[i].year == y){
                        printf("%s - %s - %s - %d\n", a[i].name, a[i].singer, a[i].composer, a[i].year);
                    }
                }
                printf("\n");
            }
            else if(v == 'e'){
                printf("\n");
                break;
            }
        }
        else if(t == 3){
            FILE *f3 = fopen(argv[1], "a+");
            char nname[100], nsinger[100], ncomposer[100];
            int nyear;
            printf("Add new song:\n");
            printf("Name: ");
            scanf(" %[^\n]%*c", nname);
            printf("Singer: ");
            scanf(" %[^\n]%*c", nsinger);
            printf("Composer: ");
            scanf(" %[^\n]%*c", ncomposer);
            printf("Year: ");
            scanf("%d", &nyear);
            fprintf(fi, "\n%s#*#%s#*#%s#*#%d", nname, nsinger, ncomposer, nyear);
            sll_push_back_song(list, nname, nsinger, ncomposer, nyear);
            a = realloc(a, sll_length(list) * sizeof(struct song_s));
            a[idx].name = sll_node_song_name(list->back);
            a[idx].singer = sll_node_song_singer(list->back);
            a[idx].composer = sll_node_song_composer(list->back);
            a[idx].year = sll_node_song_year(list->back);
            idx++;
            fclose(f3);
        }
        else if(t == 4){
            while(1){
                char v;
                char s[200];
                int y;
                printf("Delete by:\n");
                printf("a. Name\n");
                printf("b. Singer\n");
                printf("c. Composer\n");
                printf("d. Year\n");
                printf("e. Quit\n");
                printf("Choose (a-e): ");
                scanf(" %c", &v);
                fflush(stdin);
                if(v != 'a' && v != 'b' && v != 'c' && v != 'd' && v != 'e'){
                    printf("Wrong input. Choose again.\n");
                    continue;
                }
                else if(v == 'a'){
                    printf("Find name: ");
                    scanf(" %[^\n]%*c", s);
                    sll_traverse(cur, list){
                        if(cur->next != NULL && strcmp(sll_node_song_name(cur->next), s) == 0){
                            sll_node_t temp = cur->next;
                            cur->next = temp->next;
                            free(temp);
                            break;
                        }
                    }
                    for(int i = 0; i < idx; i++){
                        if(strcmp(s, a[i].name) == 0){
                            for(int j = i + 1; j < idx; j++){
                                a[j] = a[j - 1];
                            }
                            idx--;
                        }
                    }
                    delete_line_file(argv[1], s);
                }
                else if(v == 'b'){
                    printf("Find singer: ");
                    scanf(" %[^\n]%*c", s);
                    sll_traverse(cur, list){
                        if(cur->next !=  NULL && strcmp(sll_node_song_singer(cur->next), s) == 0){
                            sll_node_t temp = cur->next;
                            cur->next = temp->next;
                            free(temp);
                            break;
                        }
                    }
                    for(int i = 0; i < idx; i++){
                        if(strcmp(s, a[i].singer) == 0){
                            for(int j = i + 1; j < idx; j++){
                                a[j] = a[j - 1];
                            }
                            idx--;
                        }
                    }
                    delete_line_file(argv[1], s);
                }
                else if(v == 'c'){
                    printf("Find composer: ");
                    scanf(" %[^\n]%*c", s);
                    fflush(stdin);
                    sll_traverse(cur, list){
                        if(cur->next != NULL  && strcmp(sll_node_song_composer(cur->next), s) == 0){
                            sll_node_t temp = cur->next;
                            cur->next = temp->next;
                            free(temp);
                            break;
                        }
                    }
                    for(int i = 0; i < idx; i++){
                        if(strcmp(s, a[i].composer) == 0){
                            for(int j = i + 1; j < idx; j++){
                                a[j] = a[j - 1];
                            }
                            idx--;
                        }
                    }
                    delete_line_file(argv[1], s);
                }
                else if(v == 'd'){
                    printf("Find year: ");
                    scanf(" %[^\n]%*c", s);
                    fflush(stdin);
                    sll_traverse(cur, list){
                        if(cur->next != NULL && sll_node_song_year(cur->next) == atoi(s)){
                            sll_node_t temp = cur->next;
                            cur->next = temp->next;
                            free(temp);
                            break;
                        }
                    }
                    for(int i = 0; i < idx; i++){
                        if(a[i].year == atoi(s)){
                            for(int j = i + 1; j < idx; j++){
                                a[j] = a[j - 1];
                            }
                            idx--;
                        }
                    }
                    delete_line_file(argv[1], s);
                }
                else if(v == 'e'){
                    printf("\n");
                    break;
                }
            }
        }
        else if(t == 5){
            printf("\n");
            break;
        }
    }
    free(a);
    free(line);
    free(inf);
    sll_free_list(list);
    return 0;
}