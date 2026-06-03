#include "memory.h"
#include <string.h>

int init_memory(memory_t *mem){
	memset(mem->data, 0, sizeof(mem->data));
	int ptr = 10;
	return 1;
}

