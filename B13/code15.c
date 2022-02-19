#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#define MAX 100

const long long p = 1000000007, x = 31;

struct item{
    char name[25];
    long long price;
    struct item * next;
};

struct receipt{
    char code[25];
    long long quantity;
    long long total;
};

typedef struct item * Item;

typedef struct receipt * Receipt;

long long hash_string(char * str, int n){ //n: number of products
    long long hash = 0;
    for(int i=strlen(str)-1;i>=0;i--){
        hash = (hash * x + str[i]) % p;
    }
    return hash % n;
}

Item create(char * name, long long price){
    Item new_item = (Item)calloc(1,sizeof(struct item));
    strcpy(new_item->name,name);
    new_item->price = price;
    new_item->next = NULL;
    return new_item;
}

Item append(Item head, char * name, long long price){//nối thêm
    Item new_item = create(name,price);
    if(head == NULL){
        head = new_item;
    }
    else{
        Item cur = head;
        while(cur->next){
            cur = cur->next;
        }
        cur->next = new_item;
    }
    return head;
}

Item * input_product_list(char * filename, int * n){
    FILE * f = fopen(filename,"r");
    fscanf(f,"%d",n);
    Item * list_product = (Item*)calloc(*n,sizeof(Item));
    for(int i=0;i<*n;i++){
        char name[25] = "";
        long long price = 0;
        fscanf(f,"%s",name);
        long long index = hash_string(name,*n);
        fscanf(f,"%lld",&price);
        list_product[index] = append(list_product[index],name,price);
    }
    fclose(f);
    return list_product;
}

//thêm danh sách đặt hàng 
Receipt input_order_list(char * filename, int * m, Item * list_product, int n){
    FILE * f = fopen(filename,"r");
    fscanf(f,"%d",m);
    Receipt list_order = (Receipt)calloc(*m,sizeof(struct receipt));
    for(int i=0;i<*m;i++){
        fscanf(f,"%s %lld",list_order[i].code,&list_order[i].quantity);
        list_order[i].total = 0;
        for(int j=0;j<list_order[i].quantity;j++){
            char code[25] = "";
            long long quantity = 0;
            fscanf(f,"%s %lld",code,&quantity);
            long long index = hash_string(code,n);
            Item cur = list_product[index];
            while(cur){
                if(strcmp(cur->name,code)==0){
                    list_order[i].total += quantity * (cur->price);
                    break;
                }
                else{
                    cur = cur->next;
                }
            }
        }
    }
    fclose(f);
    return list_order;
}

void swap(Receipt a, Receipt b){
    struct receipt tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

int parent(int i){
    return (i-1)/2;
}

int left_child(int i){
    return 2*i+1;
}

int right_child(int i){
    return 2*i+2;
}

void sift_down(Receipt list_order, int m, int i){ // heapify
    int max_index = i, l = left_child(i), r = right_child(i);
    if(l<m && list_order[l].total>list_order[max_index].total){
        max_index = l;
    }
    if(r<m && list_order[r].total>list_order[max_index].total){
        max_index = r;
    }
    if(i!=max_index){
        swap(list_order+i,list_order+max_index);
        sift_down(list_order,m,max_index);
    }
    return ;
}

void build_heap(Receipt list_order, int m){
    for(int i = m/2 - 1;i>=0;i--){
        sift_down(list_order,m,i);
    }
    return ;
}

struct receipt extract_max(Receipt list_order, int * m){
    struct receipt result = list_order[0];
    swap(list_order,list_order+(*m)-1);
    (*m)--;
    sift_down(list_order,*m,0);
    return result;
}

void partial_sort(Receipt list_order, int m, int k){
    build_heap(list_order,m);
    for(int i=0;i<k;i++){
        struct receipt target = extract_max(list_order,&m);
        printf("%s\t%lld\n",target.code,target.total);
    }
    return ;
}

int main(){
    int n = 0, m = 0; // n: number of products, m: number of orders
    Item * list_product = input_product_list("p1m.txt",&n);
    Receipt list_order = input_order_list("p1m-o10k.txt",&m,list_product,n);
    partial_sort(list_order,m,3);
    return 0;
}
