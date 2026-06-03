#include "proces.h"
#include <string.h>
#include "memory.h"

int clear_reg(proces_t *pc, int ptr, int type){
	int c;
	while(c != 0){
		if(ptr >= type){perror("trying to clear mamory out of stoke\n");return -1;}
		c = pc->storeg[ptr];
		pc->storeg[ptr] = 0;
		ptr++;
	}
	return 1;
}

int init_proc(proces_t *pc){
	memset(pc->storeg, 0, sizeof(pc->storeg));
	pc->regs_ptr = REG_START;
	pc->data_ptr = DATA_START;
	pc->link_ptr = LINK_START;
	return 1;
}

int loud_from(memory_t *from, int link, proces_t *to, int Tptr, int sector){
	int c;
	while(c != -1){
		
	}
	return 1;
}

int save_to(proces_t *from, int Fptr, memory_t *to, int link, int sector){
	int c;
	while(c != -1){
		
	}
	save_links()

	return 1;
}

int save_links(proces_t *pc, int link, int size){
	if(pc->storeg[pc->link_ptr] != 0){pc->storeg[pc->link_ptr++] = link;}
	else {perror("tring to save link on existed cell");return -1;}
	if(pc->storeg[pc->link_ptr] != 0){pc->storeg[pc->link_ptr++] = size;}
	else {perror("tring to save link on existed cell");return -1;}
	return 1;
}

int delet_link(proces_t *pc, int link){
	int i, del;
	del = 0;
	for(int i = LINK_START; i < PROC_STORE_LEN - 10; i++){
		if(del){
			pc->storeg[i] = pc->storeg[i+2];
			continue;
		}

		if(link == pc->storeg[i]){
			pc->storeg[i] = 0;
			pc->storeg[i+1] = 0;
		}
	}
}

int open_file(proces_t *pc, int link, memory_t *mem){
	int i = 0;
	while(){
		if(link >= REG_END){}
		pc->storeg[pc->regs_ptr] mem->data[link];
	}
}
