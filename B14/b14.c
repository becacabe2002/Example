#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct supplier_s{
	struct supplier_s *prev;
	char name[1000];
	struct supplier_s *next;
};

typedef struct supplier_s * supplier_l;

struct product_s{
	struct supplier_s *prev;
	char name[1000];
	struct product_s *next;
}
typedef struct product_s * product_l;

typedef struct list_s{
	product_l listed_products = malloc(sizeof(product_s));
	supplier_l listed_suppliers = malloc(sizeof(supplier_s));
}* list_t;

list_t listed(char *file){
	int num;
	FILE *fp = fopen(file, "r");
	fscanf(fp,"%d", num);
	product_l list1 = malloc(sizeof(product_s));
	supplier_l list2 = malloc(sizeof(supplier_s));
	fscanf(fp, "%s %s", list1->name, list2->name);
	for(int i = 1; i <= num-1; i++){
		product_l temp1 = malloc(sizeof(product_s));
		temp1 = list1;
		supplier_l temp2 = malloc(sizeof(supplier_s));
		temp2 = list2;
		char s1[100];
		char s2[100]
		char temp2[1000];
		fscanf(fp, "%s %s", s1, s2);
		while(1){
			if(strcmp(s1,temp1->name)=0){
				break;
			}
			else if(strcmp(s1,temp1->name)>0){
				if(temp1 ->next == NULL){
					product_l new_node = malloc(sizeof(product_s));
					strcpy(new_node->name,s1);
					
				}
				temp1 = temp1->next;
				continue;
			}
			else if(strcmp(s1,temp1->name)<0){
				if(temp1->prev != NULL){

				}
			}
		}
	}
};



int main(int argc, char *argv[]){
	char command[10];
	strcpy{command, argv[1]};
	if(command == "f1"){
		listed(arg[3]);
		return 0;
	}
	else if(command == "f2"){

		return 0;
	}
	else if(command == "f3"){

		return 0;
	}
	else{
		printf("\nUsage: ./prog command (product_name) inp.txt"\n);
		return 0;
	}
}
