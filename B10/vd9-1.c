#include <stdio.h>
#include <stdio.lib>

int main(int argc, char *argc[]){
	if(argc != 3){
		printf("Usage: ./prog inp.txt 101\n");
		return 1;
	}
	int q;
	sscanf(argv[2], "%d", &q);
	FILE *f = fopen(argv[1], "r");
	int n;
	fscanf(f, "%d", &n);
	int *a = malloc(sizeof(int)*n);
	for(int i = 0; i <n; i++){
		fscanf(f, "%d", a + i);
	}
	fclose(f);

	printf("n = %d q = %d\n", n,q);
	for(int i = 0; i <n; ++i){
		printf("%d", a[i]);
	}
	printf("\n");
	return 0;
}