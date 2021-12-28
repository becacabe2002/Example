#include "cgen.h"
#include "ext/io.h"

typedef struct song{
	char *name;
	char *singer;
	char *musician;
	int year;
} *song_t;

typedef struct sll_node_song{
	char *name;
	char *singer;
	char *musician;
	int year;
	song_t info;
} *sll_node_song_t;

#define to_sll_node_song_t(n) ((sll_node_song_t)n)
#define sll_song_name(n) (to_sll_node_song_t(n)->name)
#define sll_song_singer(n) (to_sll_node_song_t(n)->singer)
#define sll_song_musician(n) (to_sll_node_song_t(n)->musician)
#define sll_song_year(n) (to_sll_node_song_t(n)->year)

int song_cmp_name(const void *v1, const void *v2){
	return strcmp(((song_t)v1)->name, ((song_t)v2)->name);
}

int song_cmp_singer(const void *v1, const void *v2){
	return strcmp(((song_t)v1)->singer, ((song_t)v2)->singer);
}

int song_cmp_musician(const void *v1, const void *v2){
	return strcmp(((song_t)v1)->musician, ((song_t)v2)->musician);
}

#define to_int(p)  (*((const int*)p))
int song_cmp_year(const void *a, const void *b){
	return to_int(a) - to_int(b);
}

sll_node_t sll_create_node_song(const char *name, const char *singer, 
																		 const char *musician, const int year)
{
	sll_node_t temp = sll_create_node();
	sll_node_song_t nsn = (sll_node_song_t)realloc(temp, sizeof(struct sll_node_song));
	strcpy(nsn->name, name);
	strcpy(nsn->singer, singer);
	strcpy(nsn->musician, musician);
	nsn->year = year;
	return (sll_node_t)nsn;
}

void sll_push_song_back(sll_t list, const char *name, const char *singer,
												const char *musician, const int year)
{
	sll_push_back(list, sll_create_node_song(name, singer, musician, year));
}

void sll_print_node_song(sll_node_t node){
	printf("\n%s\t%s\t%s\t%d\n", sll_song_name(node), sll_song_singer(node), 
															 sll_song_musician(node), sll_song_year(node));
}
void sll_print_list_song(sll_t list){
	sll_traverse(cur, list){
		sll_print_node_song(cur);
	}
}

void delete_file_line(char *argv, char *str){
	char line[50];
	char *a;
	int c = 0;
	FILE *f1 = fopen(argv, "r+");
	FILE *f2 = fopen("temp_file.txt", "w+");
	while(!feof(f1)){
		fscanf(f1, "%[^\n]%*c", line);
		a = strstr(line, str);
		if(!a){
			if(c != 0) fprintf(f2, "\n");
			fputs(line, f2);
		}
		c++;
	}
	fclose(f1);
	fclose(f2);
	remove(argv);
	rename("tmp.txt", argv);
}


//Ham chuyen tu sll sang array de thuc hien qsort
song_t sll_to_arr(sll_t list){
	int size = sll_length(list);
	song_t arr =(song_t)malloc(sizeof(struct song)*size);
	int index = 0;
	sll_traverse(cur, list){
		arr[index].name = sll_song_name(cur);
		arr[index].singer = sll_song_singer(cur);
		arr[index].musician = sll_song_musician(cur);
		arr[index].year = sll_song_year(cur);
		index++;
	}
}

// Ham in danh sach tu mang
void print_from_arr(song_t a, int length){
	for(int i = 0; i < length; i++){
		printf("\n%d.\t%s - %s - %s - %d\n", i+1, 
			a[i].name, a[i].singer, a[i].musician, a[i].year);
	}
}

/*--------------------------------------------------*/
//Ham Main
int main(){
	// kiem tra nhap file
/*	if(argc != 2){
		printf("Usage: ./prog songs.txt\n");
		return 1;
	}*/
	FILE * fp = fopen("songs9.txt", "a+");
	if(fp == NULL){
		printf("Error while opening file.\n");
		return 1;
	}

	// nhap data vao sll
	sll_t list = sll_create_list();
	char *line = (char*)malloc(100*sizeof(char));
	while(cgetline(&line, 0, fp) != NULL){
		char *name;
		char *singer;
		char *musician;
		int year;
		char *token = strtok(line, "#*#");
		if(token != NULL){
			strcpy(name, token);
			singer = strtok(NULL, "#*#");
			musician = strtok(NULL, "#*#");
			year = atoi(strtok(NULL, "#*#"));
		}
		sll_push_song_back(list, name, singer, musician, year);
		free(name); free(singer); free(musician); free(line);
	}
	

// Luu vao mang
	song_t a = sll_to_arr(list);


	fclose(fp);
	// Menu giao dien 

int choice;
while(1){
	printf("\n>>>=== Menu ===<<<\n");
	printf("1. List songs by order\n");
	printf("2. Find songs\n");
	printf("3. Add a new song\n");
	printf("4. Remove a song\n");
	printf("5. Exit program");
	printf("Your choice:(1-5)");
	scanf("%d", &choice);
	fflush(stdin);
	if(choice >5 || choice < 1){
		printf("\nYour selection is not available. Please choose another one.\n");
		continue;
	}
	else if(choice == 1){
		int choice1;
		while(1){
		printf("\nPlease choose songs order:\n");
		printf("1.1 Name order\n");
		printf("1.2 Singer order\n");
		printf("1.3 Musician order\n");
		printf("1.4 Year order\n");
		printf("1.5 Back to menu\n");
		printf("Choose (1-5): ");
		scanf("%d", &choice1);
		fflush(stdin);
		if(choice1 > 5 || choice1 <1){
			printf("Out of choices. Please choose again.\n");
			continue;
		}
		else if(choice1 == 1){
			qsort(a, sll_length(list), sizeof(struct song), song_cmp_name);
			print_from_arr(a, sll_length(list));
		}
		else if(choice1 == 2){
			qsort(a, sll_length(list), sizeof(struct song), song_cmp_singer);
			print_from_arr(a, sll_length(list));
		}
		else if(choice1 == 3){
			qsort(a, sll_length(list), sizeof(struct song), song_cmp_musician);
			print_from_arr(a, sll_length(list));
		}
		else if(choice1 == 4){
			qsort(a, sll_length(list), sizeof(struct song), song_cmp_year);
			print_from_arr(a, sll_length(list));
		}
		else break;
		}
	}
	else if(choice == 2){
		int choice2;
		char *input;
		int year_choice;
		while(1){
		printf("\n Filter by:\n");
		printf("2.1 Name\n");
		printf("2.2 Singer\n");
		printf("2.3 Musician\n");
		printf("2.4 Year\n");
		printf("2.5 Back to menu\n");
		printf("Choose(1-5):");
		scanf("%d", &choice2);
		fflush(stdin);
		if(choice2 > 5 || choice2 < 1){
			printf("Choice isn't available. Please choose again!!\n");
			continue;
		}
		else if(choice2 == 1){
			int stt = 0;
			char *name_find;
			printf("\nName you want to search:");
			scanf("%[^\n]%*c", name_find);
			fflush(stdin);
			for(int i = 0; i < sll_length(list); i++){
				if(strstr(a[i].name, name_find) != NULL){
					printf("%d\t%s - %s - %s - %d", stt+1, a[i].name, a[i].singer, a[i].musician, a[i].year);
					stt++;
				} else continue;
			}
			if(stt == 0) printf("\nNOT FOUND\n");
			free(name_find);
		}
		else if(choice2 == 2){
			int stt = 0;
			char *singer_find;
			printf("\nSinger you want to search:");
			scanf("%[^\n]%*c", singer_find);
			fflush(stdin);
			for(int i = 0; i < sll_length(list); i++){
				if(strstr(a[i].singer, singer_find) != NULL){
					printf("%d\t%s - %s - %s - %d", +1, a[i].name, a[i].singer, a[i].musician, a[i].year);
					stt++;
				} else continue;
			}
			if(stt == 0) printf("\nNOT FOUND\n");
			free(singer_find);
		}
		else if(choice2 == 3){
			int stt = 0;
			char *musician_find;
			printf("\nMusician you want to search:");
			scanf("%[^\n]%*c", musician_find);
			fflush(stdin);
			for(int i = 0; i < sll_length(list); i++){
				if(strstr(a[i].musician, musician_find) != NULL){
					printf("%d\t%s - %s - %s - %d", +1, a[i].name, a[i].singer, a[i].musician, a[i].year);
					stt++;
				} else continue;
			}
			if(stt == 0) printf("\nNOT FOUND\n");
			free(musician_find);
		}
		else if(choice2 == 4){
			int stt = 0;
			int year_find;
			printf("\nYear you want to search:");
			scanf("%d", &year_find);
			fflush(stdin);
			for(int i = 0; i < sll_length(list); i++){
				if(strstr((char*)a[i].year, (char*)year_find) != NULL){
					printf("%d\t%s - %s - %s - %d", +1, a[i].name, a[i].singer, a[i].musician, a[i].year);
					stt++;
				} else continue;
			}
			if(stt == 0) printf("\nNOT FOUND\n");
		}
		else break;
	}
}
	else{
		printf("\n>>>=== Ket thuc chuong trinh ===<<<\n");
		break;
	}
}

sll_free_list(list);
return 0;
}

