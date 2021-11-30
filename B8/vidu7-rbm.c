#include "cgen.h"
#include "ext/io.h"
#include <stdio.h>

int main(int argc, char argv[]){
	if(argc != 2){
		printf("Usage: ./prog text/lisa_all_text.txt");
		return 1;
	}
	FILE *inp = fopen(argv[1], "r");
	char *line = NULL;
	rbm_t words = rbm_create(gtype_cmp_s);
	while (cgetline(&line, 0 , inp)){
		remove_tail_lf(line);
		char *tok = strtok(line, " ");
		while(tok){
			printf("%s", tok);
			tok = strtok(NULL, " ");

			//insert -1 phan biet nut da co va nut moi
			rbm_node_t n = rbm_insert(words, gtype_s(strdup(tok)), gtype_i(-1));
			if(n->value.i == -1){
				n->value.i = 1;
			} else{
				n->value.i += 1;
			}
		}
	}
	fclose(inp);
	free(line);
	return 0;
}