#include "cgen.h"
#include <time.h>

// từ con trỏ void*, chuyển thành string  () macro ép kiểu thành chuỗi char** tương đương string //
#define to_s(s) (*(const char **)s) 

typedef struct word{
    // char * =chuỗi , char == kí tự  //
    char *w; 
    int a;
}word;

// từ con trỏ void*, chuyển thành truct word* //
#define to_word(w) (*(const word *)w) 

// so sánh string theo alphabet (dùng strcmp ) //
int cmp_inc_s(const void *a, const void *b){ 
    return strcmp(to_s(a), to_s(b));
}

// so sánh số lần xuất hiện, theo thứ tự giảm dần
int cmp_word_occurences(const void *a, const void *b){ 
    return to_word(b).a - to_word(a).a;
}

// xem lại bài 7,1 và bai7,2
int main(int argc , char *argv[]){
    clock_t start = clock();

    if (argc !=2 ) {
        // hướng dẫn mở tệp và sử dụng chương trình //
        printf("Usage: ./prog text.txt\n"); 
        return 1; // quay lại chương trinh //
    }

    // mở tệp , tên tệp là đối số đầu tiên , chế độ " read" //
    FILE *f = fopen(argv[1],"r"); 

    // lưu ý , tếp phải ở cùng thư mục chứa chương trình //
    if (!f) { 
		printf("Loi mo tep %s\n", argv[1]);
		return 1;
	} 

    sll_t list = sll_create_list(); // tạo danh sácha //
    char buff[1024];

    /*Nhập dữ liệu vào, cho vào danh sách liên kết để tìm số lượng từ, cho ngược lại vào mảng để sort*/ 
    while(!feof(f)){

        // đọc chuõi  ở file và gán vào con trỏ buff //
        fscanf(f, "%s", buff); 

        // push  node vào cuối list , node mang dữ liệu cuả con trở buff ở dạng chuỗi //
        sll_push_back_g(list,(gtype){.s = strdup(buff)}); 
    }

    int l=sll_length(list);
    char **words = calloc(l, sizeof(char*));
    int idx = 0;
   sll_traverse(cur,list){ // duyệt chuỗi //

    // gán chuỗi trong các node của danh sách vào mảng words  tăng dần //
        words[idx++] = sll_node_g_value(cur).s; 
    }
    qsort(words, l, sizeof(char*),cmp_inc_s);
    /*-------------------------------------------*/


    /*Lưu phần tử khác nhau vào word, số lần lặp được lưu lại vào word.n, text được lưu vào word.w,
    xong qsort lại để có thứ tự xuất hiện giảm dần */
    word *diffwords = calloc(l, sizeof(word));
    int mark= 0;
    idx = 0;
    diffwords[0].w=words[0]; // mark từ đầu tiên //
    for(int i=1; i<l; i++){

        // nếu phần tử đang duyệt khác phần tử ngay trước đó thi ... //
         if(strcmp(words[i],words[i-1])){ 
         idx++; // mảng các từ khác nhau //
         diffwords[idx].w=words[i]; // lưu từ mới vào mảng diffwords //

         // số lần xuất hiện của từ  bằng i - mark(chỗ đánh dấu nơi bắt đầu của mảng liên tục các từ giống nhau)
         diffwords[idx].a=i-mark; 
         mark=i;// cập nhật mark
        }
       
    }
    // qsort sắp xếp theo số lần  xuất hiện giảm dần của từ //
    qsort(diffwords, idx, sizeof(word), cmp_word_occurences); 
    printf("So luong tu: %d\n",l);
    printf("So luong tu khac nhau: %d\n",idx+1);
    for(int i=0; i<=9; i++){
        printf("%s - %d lan\n",diffwords[i].w, diffwords[i].a);
    }
    /*-------------------------------------------*/
    sll_free_list(list);
    free(diffwords);
    free(words);
    fclose(f);
    clock_t end = clock();
    double time_process = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Thoi gian xu ly: %lf\n",time_process);
    return 0;
}