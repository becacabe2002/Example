/*
MINH HOẠ HÀNG ĐỢI ƯU TIÊN
*/

#include "cgen.h"

int gtype_max_d(gtype v1, gtype v2){
	return v1.d - v2.d;
}

int main(){
	p1w_t q = create_p1w(gtype_max_d);
	p1w_enqueue(q, gtype_d(1.0));
	p1w_enqueue(q, gtype_d(3.0));
	p1w_enqueue(q,gtype_d(2.0));
	while(!p1w_is_empty(q)){
		gtype value = plw_dequeue(q);
		printf("%f\n", value.d);
	}
	return 0;
}