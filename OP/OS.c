#include "proces.h"
#include "memory.h"
#include <stdio.h>

int main(){
	printf("hi\n");
	proces_t procs;
	init_proc(&procs);
	for(int i = 0; i < PROC_STORE_LEN; i++){
		printf("%d : %d\n",i, procs.storeg[i]);
	}
}
